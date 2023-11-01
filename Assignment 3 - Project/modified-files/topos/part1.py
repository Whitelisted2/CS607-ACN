#!/usr/bin/python3

from mininet.topo import Topo
from mininet.net import Mininet
from mininet.util import dumpNodeConnections
from mininet.cli import CLI


class part1_topo(Topo):
    def build(self):
        # pass
        # we add the central switch using the helper code:
        # switch1 = self.addSwitch('switchname')
        s1 = self.addSwitch('s1')

        # we want to create 4 hosts. we use the helper code:
        # host1 = self.addHost('hostname')
        # self.addLink(hostname,switchname)
        for i in range(4):
            hname = "h"+str(i+1)
            self.addHost(hname)
            self.addLink(hname, s1)

topos = {"part1": part1_topo}

if __name__ == "__main__":
    t = part1_topo()
    net = Mininet(topo=t)
    net.start()
    CLI(net)
    net.stop()
