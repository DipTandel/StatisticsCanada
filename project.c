#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//putting the entire file in a custom structure
typedef struct {
    int date;
    char geo[31];
    char dguid[12];
    char agegroup[18];
    char sex[8];
    char indicators[9];
    char characteristics[8];
    char uom[8];
    int uomid;
    char scalarfactor[6];
    int scalarid;
    char vector[11];
    char coordinate[12];
    float value;
    char status[2];
    char symbol[2];
    char terminated[2];
    int decimals;
} sheet;

//function to remove quotes from string
void cleanint(char *input) {
    int j = 0;
    //goes through the whole string and rewrites it without quotes
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != '"') {
            input[j++] = input[i];
        }
    }
    input[j] = '\0'; //adds \0 at end of string to marks the end
}

//function to calculate the avg population of a province with diabetes for a specific year
float yearlyavg(int start, int end, int year, sheet s[210]) { 
	float avg = 0;
	int counter = 0; 
	for (int i = start; i <= end; i++) {
		if (s[i].value != 0 && s[i].date == year) { //dont count empty values and only count the values of the year needed
			avg = avg + s[i].value;
			counter++;
		}
	}
	return (avg/counter);
}

//function to calculate the avg population of a province with diabetes across an age range
float ageavg(int start, int end, char *range, sheet s[210]) { 
	float avg = 0;
	int counter = 0; 
	for (int i = start; i <= end; i++) {
		//strcmp() works by comparing 2 strings and returning 0 if they are the same
		if (s[i].value != 0 && strcmp(s[i].agegroup,range) == 0) { //dont count empty values and only count the age range needed
			avg = avg + s[i].value;
			counter++;
		}
	}
	return (avg/counter);
}

int main (){
	
	//the spreadsheet has 210 rows
	sheet s[210];
	
	FILE* data = fopen("statscan_diabetes.csv", "r");
	//variable of file is now "data"
		
	int linelength = 255; //arbitrarily chosen length of a single line
	char line[linelength]; //this will hold the line
	
	//read the header line here to prevent it from being read in the loop
	fgets(line, linelength, data);
	
	char *sp; //temporary pointer
	
	//loop which will read data line by line
	int i = 0; //index of line
	
	while (i < 210) { //indicates end of line
		//printf("\n%s", line);
		fgets(line, linelength, data);
		//convert date from string to int and save
		sp = strtok(line, ",");
		cleanint(sp);
		s[i].date = atoi(sp);
		printf("%d - ", s[i].date);
		
		//save geo
		sp = strtok(NULL, ","); //read from where left of till another comma
		cleanint(sp);
		strcpy(s[i].geo,sp);
		printf("%s - ", s[i].geo);
		
		//save dguid
		sp = strtok(NULL, ","); //read from where left of till another comma
		cleanint(sp);
		strcpy(s[i].dguid,sp);
		printf("%s - ", s[i].dguid);
		
		//save agegroup
		sp = strtok(NULL, ","); //read from where left of till another comma
		cleanint(sp);
		strcpy(s[i].agegroup,sp);
		printf("%s - ", s[i].agegroup);
		
		//save sex
		sp = strtok(NULL, ","); //read from where left of till another comma
		cleanint(sp);
		strcpy(s[i].sex,sp);
		printf("%s - ", s[i].sex);
		
		//save indicators
		sp = strtok(NULL, ","); //read from where left of till another comma
		cleanint(sp);
		strcpy(s[i].indicators,sp);
		printf("%s - ", s[i].indicators);
		
		//save characteristics
		sp = strtok(NULL, ","); //read from where left of till another comma
		cleanint(sp);
		strcpy(s[i].characteristics,sp);
		printf("%s - ", s[i].characteristics);
		
		//save uom
		sp = strtok(NULL, ","); //read from where left of till another comma
		cleanint(sp);
		strcpy(s[i].uom,sp);
		printf("%s - ", s[i].uom);
		
		//convert uomid from string to int and save
		sp = strtok(NULL, ",");
		cleanint(sp);
		s[i].uomid = atoi(sp);
		printf("%d - ", s[i].uomid);
		
		//save scalarfactor
		sp = strtok(NULL, ","); //read from where left of till another comma
		cleanint(sp);
		strcpy(s[i].scalarfactor,sp);
		printf("%s - ", s[i].scalarfactor);
		
		//convert scalarid from string to int and save
		sp = strtok(NULL, ",");
		cleanint(sp);
		s[i].scalarid = atoi(sp);
		printf("%d - ", s[i].scalarid);
		
		//save vector
		sp = strtok(NULL, ","); //read from where left of till another comma
		cleanint(sp);
		strcpy(s[i].vector,sp);
		printf("%s - ", s[i].vector);
		
		//save coordinate
		sp = strtok(NULL, ","); //read from where left of till another comma
		cleanint(sp);
		strcpy(s[i].coordinate,sp);
		printf("%s - ", s[i].coordinate);
		
		//convert value from string to float and save
		sp = strtok(NULL, ",");
		cleanint(sp);
		s[i].value = atof(sp);
		printf("%.2f - ", s[i].value);
		
		//save status
		sp = strtok(NULL, ","); //read from where left of till another comma
		cleanint(sp);
		strcpy(s[i].status,sp);
		printf("%s - ", s[i].status);
		
		//save symbol
		sp = strtok(NULL, ","); //read from where left of till another comma
		cleanint(sp);
		strcpy(s[i].symbol,sp);
		printf("%s - ", s[i].symbol);
		
		//save terminated
		sp = strtok(NULL, ","); //read from where left of till another comma
		cleanint(sp);
		strcpy(s[i].terminated,sp);
		printf("%s - ", s[i].terminated);
		
		//convert decimals from string to int and save
		sp = strtok(NULL, ",");
		cleanint(sp);
		s[i].decimals = atoi(sp);
		printf("%d \n", s[i].decimals);
		
		i++;
	}
	//close file (end)
	fclose(data);
	printf("\n");
	
	
	printf("//----------Q1a)----------//\n");
	//average percentage of the whole population of Quebec with diabetes
	float qcAvg = 0;
	int counter1 = 0; 
	for (int i = 42; i <= 83; i++) { //lines for Quebec
		if (s[i].value != 0) { //dont count empty values
			qcAvg = qcAvg + s[i].value;
			counter1++;
		}
	}
	qcAvg = qcAvg/counter1;
	printf("The Average percentage of the whole population of Quebec with diabetes from 2015 to 2021 (inclusive): %f\n", qcAvg);
	//average percentage of the whole population of Ontario with diabetes
	float onAvg = 0;
	int counter2 = 0; 
	for (int i = 84; i <= 125; i++) { //lines for Ontario
		if (s[i].value != 0) { //dont count empty values
			onAvg = onAvg + s[i].value;
			counter2++;
		}
	}
	onAvg = onAvg/counter2;
	printf("The Average percentage of the whole population of Ontario with diabetes from 2015 to 2021 (inclusive): %f\n", onAvg);
	//average percentage of the whole population of Alberta with diabetes
	float abAvg = 0;
	int counter3 = 0; 
	for (int i = 126; i <= 167; i++) { //lines for Alberta
		if (s[i].value != 0) { //dont count empty values
			abAvg = abAvg + s[i].value;
			counter3++;
		}
	}
	abAvg = abAvg/counter3;
	printf("The Average percentage of the whole population of Alberta with diabetes from 2015 to 2021 (inclusive): %f\n", abAvg);
	//average percentage of the whole population of British Columbia with diabetes
	float bcAvg = 0;
	int counter4 = 0; 
	for (int i = 168; i <= 209; i++) { //lines for British Columbia
		if (s[i].value != 0) { //dont count empty values
			bcAvg = bcAvg + s[i].value;
			counter4++;
		}
	}
	bcAvg = bcAvg/counter4;
	printf("The Average percentage of the whole population of British Columbia with diabetes from 2015 to 2021 (inclusive): %f \n \n", bcAvg);
	
	
	printf("//----------Q1b)----------//\n");
	//average percentage of the whole population of Canada with diabetes
	float canAvg = 0;
	int counter5 = 0; 
	for (int i = 0; i <= 41; i++) { //lines for Canada
		if (s[i].value != 0) { //dont count empty values
			canAvg = canAvg + s[i].value;
			counter5++;
		}
	}
	canAvg = canAvg/counter5;
	printf("The Average percentage of the whole population of Canada with diabetes from 2015 to 2021 (inclusive): %f\n\n", canAvg);
	
	
	printf("//----------Q1c)----------//\n");
	//yearly average percentages of the whole population of Quebec with diabetes
	float qcAvgList[7];
	for (int i = 2015; i <= 2021; i++) {
		qcAvgList[i-2015] = yearlyavg(42, 83, i, s);
		printf("The %d Average percentage of the whole population of Quebec with diabetes: %f\n", i, qcAvgList[i-2015]);
	}
	printf("\n");
	//yearly average percentages of the whole population of Ontario with diabetes
	float onAvgList[7];
	for (int i = 2015; i <= 2021; i++) {
		onAvgList[i-2015] = yearlyavg(84, 125, i, s);
		printf("The %d Average percentage of the whole population of Ontario with diabetes: %f\n", i, onAvgList[i-2015]);
	}
	printf("\n");
	//yearly average percentages of the whole population of Alberta with diabetes
	float abAvgList[7];
	for (int i = 2015; i <= 2021; i++) {
		abAvgList[i-2015] = yearlyavg(126, 167, i, s);
		printf("The %d Average percentage of the whole population of Alberta with diabetes: %f\n", i, abAvgList[i-2015]);
	}
	printf("\n");
	//yearly average percentages of the whole population of British Columbia with diabetes
	float bcAvgList[7];
	for (int i = 2015; i <= 2021; i++) {
		bcAvgList[i-2015] = yearlyavg(168, 209, i, s);
		printf("The %d Average percentage of the whole population of British Columbia with diabetes: %f\n", i, bcAvgList[i-2015]);
	}
	printf("\n");
	//yearly average percentages of the whole population of Canada with diabetes
	float canAvgList[7];
	for (int i = 2015; i <= 2021; i++) {
		canAvgList[i-2015] = yearlyavg(0, 41, i, s);
		printf("The %d Average percentage of the whole population of Canada with diabetes: %f\n", i, canAvgList[i-2015]);
	}
	printf("\n");
	
	
	printf("//----------Q1d)----------//\n");
	char ageRangeList[3][18] = {"35 to 49 years","50 to 64 years","65 years and over"}; //will be used to easily pass to function
	//average percentage of the population of Quebec with diabetes within an age group
	float qcAgeList[3];
	for (int i = 0; i < 3; i++) {
		qcAgeList[i] = ageavg(42, 83, ageRangeList[i], s);
		printf("The Average percentage from 2015 to 2021 (inclusive) of the population of Quebec with diabetes from ages %s is: %f\n", ageRangeList[i], qcAgeList[i]);
	}
	printf("\n");
	//average percentage of the population of Ontario with diabetes within an age group
	float onAgeList[3];
	for (int i = 0; i < 3; i++) {
		onAgeList[i] = ageavg(84, 125, ageRangeList[i], s);
		printf("The Average percentage from 2015 to 2021 (inclusive) of the population of Ontario with diabetes from ages %s is: %f\n", ageRangeList[i], onAgeList[i]);
	}
	printf("\n");
	//average percentage of the population of Alberta with diabetes within an age group
	float abAgeList[3];
	for (int i = 0; i < 3; i++) {
		abAgeList[i] = ageavg(126, 167, ageRangeList[i], s);
		printf("The Average percentage from 2015 to 2021 (inclusive) of the population of Alberta with diabetes from ages %s is: %f\n", ageRangeList[i], abAgeList[i]);
	}
	printf("\n");
	//average percentage of the population of British Columbia with diabetes within an age group
	float bcAgeList[3];
	for (int i = 0; i < 3; i++) {
		bcAgeList[i] = ageavg(168, 209, ageRangeList[i], s);
		printf("The Average percentage from 2015 to 2021 (inclusive) of the population of British Columbia with diabetes from ages %s is: %f\n", ageRangeList[i], bcAgeList[i]);
	}
	printf("\n");
	//average percentage of the population of Canada with diabetes within an age group
	float canAgeList[3];
	for (int i = 0; i < 3; i++) {
		canAgeList[i] = ageavg(0, 41, ageRangeList[i], s);
		printf("The Average percentage from 2015 to 2021 (inclusive) of the population of Canada with diabetes from ages %s is: %f\n", ageRangeList[i], canAgeList[i]);
	}
	printf("\n");
	
		printf("//----------Q2)----------//\n");
	// Determine which province has the highest and lowest percentage of diabetes
	float minPercentage = qcAvg;
	float maxPercentage = qcAvg;
	char *minProvince = "Quebec";
	char *maxProvince = "Quebec";

	if (onAvg < minPercentage) {
		minPercentage = onAvg;
		minProvince = "Ontario";
	} else if (onAvg > maxPercentage) {
		maxPercentage = onAvg;
		maxProvince = "Ontario";
	}

	if (abAvg < minPercentage) {
		minPercentage = abAvg;
		minProvince = "Alberta";
	} else if (abAvg > maxPercentage) {
		maxPercentage = abAvg;
		maxProvince = "Alberta";
	}

	if (bcAvg < minPercentage) {
		minPercentage = bcAvg;
		minProvince = "British Columbia";
	} else if (bcAvg > maxPercentage) {
		maxPercentage = bcAvg;
		maxProvince = "British Columbia";
	}

	printf("The province with the highest percentage of diabetes (all years and age groups): %s\n", maxProvince);
	printf("The province with the lowest percentage of diabetes (all years and age groups): %s\n\n", minProvince);

	printf("//----------Q3)----------//\n");
	// Indicate provinces with diabetes percentages above and below the national average
	printf("Provinces with diabetes percentages above the national average (all years and age groups):\n");
	if (qcAvg > canAvg) printf("Quebec\n");
	if (onAvg > canAvg) printf("Ontario\n");
	if (abAvg > canAvg) printf("Alberta\n");
	if (bcAvg > canAvg) printf("British Columbia\n");

	printf("\nProvinces with diabetes percentages below the national average (all years and age groups):\n");
	if (qcAvg < canAvg) printf("Quebec\n");
	if (onAvg < canAvg) printf("Ontario\n");
	if (abAvg < canAvg) printf("Alberta\n");
	if (bcAvg < canAvg) printf("British Columbia\n");

	printf("\n");

	printf("//----------Q4)----------//\n");
	// Indicate which year and province have the highest and lowest percentage of diabetes
	int maxYear = 2015, minYear = 2015;
	char *maxYearProvince = "Quebec";
	char *minYearProvince = "Quebec";
	float maxYearPercentage = qcAvgList[0];
	float minYearPercentage = qcAvgList[0];

	for (int year = 2015; year <= 2021; year++) {
		int index = year - 2015;
		if (qcAvgList[index] < minYearPercentage) {
			minYearPercentage = qcAvgList[index];
			minYear = year;
			minYearProvince = "Quebec";
		} else if (qcAvgList[index] > maxYearPercentage) {
			maxYearPercentage = qcAvgList[index];
			maxYear = year;
			maxYearProvince = "Quebec";
		}

		if (onAvgList[index] < minYearPercentage) {
			minYearPercentage = onAvgList[index];
			minYear = year;
			minYearProvince = "Ontario";
		} else if (onAvgList[index] > maxYearPercentage) {
			maxYearPercentage = onAvgList[index];
			maxYear = year;
			maxYearProvince = "Ontario";
		}

		if (abAvgList[index] < minYearPercentage) {
			minYearPercentage = abAvgList[index];
			minYear = year;
			minYearProvince = "Alberta";
		} else if (abAvgList[index] > maxYearPercentage) {
			maxYearPercentage = abAvgList[index];
			maxYear = year;
			maxYearProvince = "Alberta";
		}

		if (bcAvgList[index] < minYearPercentage) {
			minYearPercentage = bcAvgList[index];
			minYear = year;
			minYearProvince = "British Columbia";
		} else if (bcAvgList[index] > maxYearPercentage) {
			maxYearPercentage = bcAvgList[index];
			maxYear = year;
			maxYearProvince = "British Columbia";
		}
	}

	printf("The year and province with the highest percentage of diabetes (all age groups): %d, %s\n", maxYear, maxYearProvince);
	printf("The year and province with the lowest percentage of diabetes (all age groups): %d, %s\n\n", minYear, minYearProvince);

	printf("\n//----------Final Note----------//\nQuestions 5 & 6 are done with GNU Plot");
	return (0);
}
