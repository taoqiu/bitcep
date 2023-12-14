# bitcep

Welcome to BitCEP complex event matching algorithm. 
Please load this project using the Visual Studio 2022 IDE in a Windows environment for smooth execution.
The event streams and queries that serve as input examples are stored in the "data" and "query" folders respectively, located at the same level directory.
The detailed matching results are stored in the "result" folder, which is located at the same level directory,too.

The configuration properties of BitCEP are set in the document config.txt.The specific content is shown below:
The first line and the second line are respectively the relative addresses of the input query and event stream.
The third line is the number of times the program is executed in a loop, which facilitates measuring the average running time.
The fourth line is the size of the time slice, with a default unit of seconds. It can be adjusted based on the specific dataset.
The last line is the relative address for saving detailed matching results.

Note: When debugging, please set the SDL check in the properties of the solution in vs2022 to "No".

After modifying the file path in the RunBitCEP.bat file to the new storage path, which is the current location of the file, 
you can run the BitCEP program under the default configuration conditions by clicking on the RunBitCEP file. 
After it outputs all the information of the matching results, you can enter any content to end the execution of the program.
