To run do:
* `make` (builds the code)
* `./a.out` (runs the program and generates an image for the full data area)
    * * In this mode every point of data is a 1 pixel square
    * * By default it only takes 4 000 000 points of the data (can be changed in pgHelpers.cpp find_all, change the LIMIT in the SQL query) 
* `./a.out <FROM AIRPORT CODE> <TO AIRPORT CODE>` (runs the code and generates an image for the flights from the airport to the other airport)
    * * This command generates one image per flight between the airports with the fligth marked in yellow
    * *  In this mode every point of data is a 10 pixel square

The only dependency is the postgres library (same as in postgressqlinsertedcxx, look there for install directions). Look in the postgressqlinsertercxx repository for directions on how to install. 

All images are placed in target/
