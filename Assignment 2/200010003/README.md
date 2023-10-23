### Instructions for running the code
---
Some of this has been mentioned in the technical report, but follow these steps to run the sample input for the code.
1. Compile the program with ```g++ main.cpp -o main.o```.
2. If you want to run the program with a specific set of parameters, go ahead with ```./main.o (<parameter-flag> <parameter-value>)*```, where * denotes zero or more occurrences. If any parameters are not specified, their default values will be used.
3. If you want to run the sample input, run ```bash run.sh```. The output will be saved in ```output.txt``` in the same folder as this very README.md file.
4. The graphs were generated using the helper_scripts, which can also be used to generate some sample input. In case of errors, ensure that an ```output/``` folder is present in the root directory of this project when running the script files, prior to executing cells in the jupyter notebook.

### Other info
---
- Images and inferences are all enclosed in the file ```CS607_Report_A2_200010003.pdf```. A few points about the input parameters are also explained there.
- Ensure that required python libraries / a recent g++ version is used, to ensure smooth working of the program.
- ```output.txt``` contains some sample output, and this is also pasted at the end of the program file ```main.cpp```