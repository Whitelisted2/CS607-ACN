#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sys/stat.h>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

// Initialize local Variables
int switchportcount, buffersize, maxtimeslots;    // switchportcount = N, buffersize = B, maxtimeslots = T
float K;                                          // K = knockout
float packetgenprob;                              // packetgenprob
string qType = "";                                // scheduling algorithm (INQ/KOUQ/ISLIP)
string outputfile = "output.txt";                 // text file to store output (default value)
int total_drops = 0;                              // count total drops (KOUQ)
vector<double> delay;                             // collect delay values
vector<int> lastUsedPort;                         // to check if output port is free or busy
map<int, int> LU_map;                             // collect link utilization info
vector<vector<int>> RequestMatrix;                // request matrix (ISLIP)
double link_util = 0, avg_delay = 0, std_dev = 0; // initial values for perf metrics

// Packet structure to store arrival time, destination port
struct Packet {
    int destination_port;
    double arrival_time;
};

// to set defaults in case no provided values
void SetDefault() {
    switchportcount = 8;
    buffersize = 4;
    maxtimeslots = 10000;
    K = 0.6;                    /////////
    packetgenprob = 0.5;
    qType = "INQ";
    outputfile = "output.txt";
}

// decide if packet generates, based on packetgenprob
bool IsPacketGenerated() {
    if (packetgenprob == 1)
        return true;
    if (((double)rand() / (RAND_MAX)) > packetgenprob)
        return false;
    return true;
}

// check if a certain I/P buffer has space
bool IsBufferSpaceAvailable(vector<vector<Packet>> &queue, int port) {
    if (queue[port].size() >= buffersize)
        return false;
    return true;
}

// generate traffic
void TrafficGenerator(vector<vector<Packet>> &queue, int t) {
    int out_port;
    if (qType == "INQ")
    {
        for (int in_port = 0; in_port < switchportcount; in_port++) // generate packets at each input port
        {
            if (IsPacketGenerated() && IsBufferSpaceAvailable(queue, in_port)) // if the packet gen in favour and buffer not full
            {
                out_port = rand() % switchportcount; // generate the output port for the packet randomly
                struct Packet p;
                p.destination_port = out_port; // set the output port for the packet
                p.arrival_time = t;            // set the arrival time for the packet
                queue[in_port].push_back(p);   // puch packet in the queue of that input port
            }
        }
    }
    else if (qType == "KOUQ") {
        int count[switchportcount]; // count number of packets in each port
        memset(count, 0, sizeof(count));
        for (int in_port = 0; in_port < switchportcount; in_port++)
        {
            if (IsPacketGenerated()) // check the packet probability condition
            {
                out_port = rand() % switchportcount;   // generate the output port for the packet randomly
                count[out_port]++;       // increases the packet count for that output port
                if (count[out_port] > K) // if packets for the output port is higher that K, increases the drop count
                {
                    total_drops += count[out_port] == (K + 1) ? 1 : 0;
                    continue;
                }
                else if (IsBufferSpaceAvailable(queue, in_port)) // if there is space in buffer push tha packet inside queue
                {
                    struct Packet p;
                    p.destination_port = out_port; // set the output port for the packet
                    double time = t + ((double)in_port / 10000);
                    p.arrival_time = time;        // set the arrival time for the packet
                    queue[out_port].push_back(p); // puch packet in the queue of that input port
                }
            }
        }
    }
    else if (qType == "ISLIP") {
        for (int in_port = 0; in_port < switchportcount; in_port++)
        {
            if (IsPacketGenerated() && IsBufferSpaceAvailable(queue, in_port))
            {
                out_port = rand() % switchportcount; // randomly choose dest port
                struct Packet p;
                p.destination_port = out_port;
                p.arrival_time = t;          // arr time = curr time
                queue[in_port].push_back(p); // append to input port queue
                RequestMatrix[out_port][in_port] = 1; // request matrix set
            }
        }
    }
}

// grant for ISLIP
int GrantPort_ISLIP(int out_port, bool *port_used) {
    // checks free input port which is next to recently used one
    for (int i = lastUsedPort[out_port] + 1; i < switchportcount; i++) {
        // if input port i has requested for output port out_port and i is free
        if (RequestMatrix[out_port][i] == 1 && port_used[i] == false) {
            port_used[i] = true; // return index of selected input port if granted
            return i;
        }
    }
    for (int i = 0; i <= lastUsedPort[out_port]; i++) {
        if (RequestMatrix[out_port][i] == 1 && port_used[i] == false) {
            port_used[i] = true;
            return i;
        }
    }
    return -1; // if no grant
}

// find output port for packet in ISLIP
int GetOutPort_ISLIP(vector<vector<Packet>> &queue, int in_port, int out_port) {
    int n = queue[in_port].size();
    for (int i = 0; i < n; i++) {
        if (queue[in_port][i].destination_port == out_port)
            return i;
    }
    return -1; // if no output port 
}

// main scheduling region!
void scheduler(vector<vector<Packet>> &queue, int curr_time) {
    bool port_used[switchportcount]; // checks if the output port is used on free
    memset(port_used, false, sizeof(port_used));

    if (qType == "INQ") { // INQ scheduling here
        for (int port = 0; port < switchportcount; port++) {
            // for each input port if its queue contains any packet to schedule and required output port is not used
            if (queue[port].size() > 0 && port_used[queue[port][0].destination_port] == false) {
                delay.push_back(curr_time - queue[port][0].arrival_time + 1); // calc delay
                queue[port].erase(queue[port].begin());                       // packet removed from queue
                LU_map[port]++;                                               // to keep track of link utilization
                port_used[queue[port][0].destination_port] = true;            // to update used ports
            }
        }
    }
    else if (qType == "KOUQ") { // KOUQ scheduling here
        for (int port = 0; port < switchportcount; port++) {
            // for each input port if its queue contains any packet to schedule
            if (queue[port].size() > 0) {
                delay.push_back(curr_time - queue[port][0].arrival_time + 1); // calculate delay
                queue[port].erase(queue[port].begin());                       // packet removed from queue
                LU_map[port]++;                                               // to keep track of link utilization
            }
        }
    }
    else if (qType == "ISLIP") {
        // grant phase with sort of round robin
        for (int out_port = 0; out_port < switchportcount; out_port++) {
            lastUsedPort[out_port] = GrantPort_ISLIP(out_port, port_used);
        }
        // accept phase where transmissions decided. metrics calculated.
        for (int out_port = 0; out_port < switchportcount; out_port++) {
            int in_port = lastUsedPort[out_port];
            if (in_port != (-1)) {
                int p_idx = GetOutPort_ISLIP(queue, in_port, out_port);
                if (p_idx == -1)
                    continue;
                RequestMatrix[out_port][in_port] = 0;                                // request granted
                delay.push_back(curr_time - queue[in_port][p_idx].arrival_time + 1); // delay calculated
                queue[in_port].erase(queue[in_port].begin() + p_idx);                // remove pkt from queue
                LU_map[in_port]++;                                                   // LU keep track
            }
        }
    }
}

// function to calculate standard deviation of delay (proper method)
float StdDevCalculator(int avg_delay) {
    float std_dev = 0.0;
    for (auto d : delay)
        std_dev += pow(d - avg_delay, 2);
    return sqrt(std_dev / delay.size());
}

// function to calculate performance metrics. can print if want
void EvalPerfMetrics() {
    link_util = 0;
    avg_delay = 0;
    for (auto itr = LU_map.begin(); itr != LU_map.end(); itr++) // to calculate avg link utilization
        link_util += (itr->second);
    link_util /= (LU_map.size() * maxtimeslots);
    // std::cout << "avg_LU : " << link_util << endl;

    for (int i = 0; i < delay.size(); i++) // to calculate avg delay
        avg_delay += delay[i];
    avg_delay /= (delay.size());
    // std::cout << "avg_PD : " << avg_delay << endl;

    std_dev = StdDevCalculator(avg_delay); // to calculate standard deviation of delay
    // std::cout << "stddev_PD : " << std_dev << endl;

    if (qType == "KOUQ") // packet drop probability in case of KOUQ
    {
        long double K_drop = (long double)total_drops / (switchportcount * maxtimeslots);
        // std::cout << "K_drop_prob : " << K_drop << endl;
    }
}

// check if outfile exists
inline bool DoesFileExist(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

// write to output file
void FileWrite(string outputfile) {
    ofstream outfile;
    if (!DoesFileExist(outputfile)) // if file doesn't exist
    {
        outfile.open(outputfile, std::ios_base::app);
        // write header for the first time
        // outfile << "[For default value of maxtimeslot = " << maxtimeslots << " ,pktgenprob = " << packetgenprob << " ]" << endl;
        // outfile << "switchportcount\t\tp\t\tBuffer Size\t\tQueue type\t\tAvg PD\t\tStd Dev PD\t\tAvg link utilization" << endl;
        outfile.close();
    }
    // open file in append mode
    outfile.open(outputfile, std::ios_base::app);
    // write results to the output file
    cout << "N\tp\tQtype\tAvg PD\tStd. Dev of PD\tAvg LU" << endl;
    outfile << switchportcount << "\t" << packetgenprob << "\t" << qType << "\t" << avg_delay << "\t" << std_dev << "\t" << link_util << endl;
    std::cout << switchportcount << "\t" << packetgenprob << "\t" << qType << "\t" << avg_delay << "\t" << std_dev << "\t" << link_util << endl;

}

// driver function
int main(int argc, char **argv) {
    SetDefault();                       // set default values
    int flag = 1, curr = 1;
    while (curr < argc) {               // read cmd line, use defaults if no vals for anything
        if (curr + 2 >= argc + 1) {     // check so as to not overflow
            flag = 0;
            break;
        }
        if (strcmp(argv[curr], "-N") == 0)
            switchportcount = atoi(argv[curr + 1]);
        else if (strcmp(argv[curr], "-B") == 0)
            buffersize = atoi(argv[curr + 1]);
        else if (strcmp(argv[curr], "-p") == 0)
            packetgenprob = atof(argv[curr + 1]);
        else if (strcmp(argv[curr], "-queue") == 0)
            qType = argv[curr + 1];
        else if (strcmp(argv[curr], "-K") == 0)
            K = atof(argv[curr + 1]);
        else if (strcmp(argv[curr], "-out") == 0)
            outputfile = argv[curr + 1];
        else if (strcmp(argv[curr], "-T") == 0)
            maxtimeslots = atol(argv[curr + 1]);
        else {
            flag = 0;
            break;
        }
        curr = curr + 2; // move to next arg
    }
    K = K * switchportcount; // knockout calc

    srand(time(NULL));

    // maintain queue for each port to store packets
    vector<vector<Packet>> queue(switchportcount);

    if (qType == "ISLIP") // for islip, initialize lastUsedPort and RequestMatrix
    {
        lastUsedPort = vector<int>(switchportcount, -1);
        RequestMatrix = vector<vector<int>>(switchportcount, vector<int>(switchportcount, 0));
    }
    for (int t = 0; t < maxtimeslots; t++)  // run for each timeslot
    {
        TrafficGenerator(queue, t);         // traffic generation
        scheduler(queue, t);                // scheduling of the traffic
    }
    EvalPerfMetrics();                      // evaluate performance metrics
    FileWrite(outputfile);                  // write the content to the file
    return 0;
}

/*
Sample output

8	0.8	INQ	4.07987	2.95932	0.66295
8	0.8	KOUQ	2.161	1.36132	0.737838
8	0.8	ISLIP	6.77393	11.843	0.567638

*/