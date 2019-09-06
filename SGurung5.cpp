//============================================================================
// Name        : SGurung5.cpp
// Author      : Sanjay Gurung
// Version     :
// Copyright   : Your copyright notice
// Description : Gitlins Match Game
//============================================================================

#include <iostream>
#include <vector>
#include<ctime>
#ifdef __APPLE__
#include <unistd.h>
#endif
using namespace std;

vector<int> randoms; //single vector
vector<int> randomIndex;
vector<vector<int> > visibleboard; //visible board that has nested vector and grids

bool foundIndex(int index){
	bool found = false;
	for (int i =0; i< randomIndex.size(); i++ ){
		if(index == randomIndex[i]) {
			found = true;
		}
	}
	if(found) {

		return true;
	}else {
		randomIndex.push_back(index);
	}
	return false;
}


int getRandomKeys (bool b) {
	if(b){

		int randomInt = rand() % randoms.size(); //randomly choose

		while (foundIndex(randomInt)) {

			randomInt = rand() % randoms.size(); //randomly choose
		}
		return randoms[randomInt];

	}else{
		int randomInt = rand() % 25 + 64; //randomly choose
		randoms.push_back(randomInt);
		return randomInt;
	}
}
//board that shows number board
void showBoard() {
	int counter = 1;
	for(int i=0; i<visibleboard.size();i++) {
			for(int j=0; j<visibleboard[i].size();j++) {
				cout <<counter<<"\t" << " ";
				counter++;
			}
			cout << endl;
		}
}
//board that shows character behind board
void showBoard1(){
	for(int i=0; i<visibleboard.size();i++) {
				for(int j=0; j<visibleboard[i].size();j++) {
					cout<< (char)visibleboard[i][j] <<"\t";
				}
				cout << endl;
			}

}
bool showBoardWithOptions(int first, int second) {
	int firstI = 0;
	int firstJ = 0;
	int secondI = 0;
	int secondJ = 0;

	int counter = 1;
	for(int i=0; i<visibleboard.size();i++) {
		for(int j=0; j<visibleboard[i].size();j++) {
			if ((int)visibleboard[i][j] > 99) {
				int val = (int)visibleboard[i][j]- (int)100;
				cout<< (char)val<<"\t";
			}else if (counter == first || counter == second) {
				cout<< (char)visibleboard[i][j] <<"\t";
			}else{
				//cout <<counter<<"\t" << " ";
				cout <<(int)visibleboard[i][j]<<"\t";
			}
			if( counter  == first ){
				firstI=i;
				firstJ=j;
			}
			if( counter == second ) {
				secondI=i;
				secondJ=j;
			}
			counter++;
		}
		cout << endl;
	}
	if (visibleboard[firstI][firstJ] == visibleboard[secondI][secondJ]){

		visibleboard[firstI][firstJ] = (int)visibleboard[firstI][firstJ] + 100;
		visibleboard[secondI][secondJ] = (int)visibleboard[secondI][secondJ] +100;
		return true;
	}
	cout << endl;
	return false;

}

int main() {

	int row;
	int col;
	int product;
	   time_t timer, now; // for timer
		struct tm y2k = { 0 };
		double seconds, sec; //intilization

		y2k.tm_hour = 0;
		y2k.tm_min = 0;
		y2k.tm_sec = 0;
		y2k.tm_year = 100;
		y2k.tm_mon = 0;
		y2k.tm_mday = 1;
	srand(time(NULL));


	cout<<"In this game, pairs of letters will be hidden on a rectangular grid."<<endl;
	cout<<"Once the grid is established you will be asked to enter the numbers of two slots."<<endl;
	cout<<"If the letters at those slots match,they will stay in view."<<endl;
	cout<<"If not,after 3 seconds the letter will disappear and be replaced by the numbers."<<endl;
	cout<<"Your job is to find all the pairs"<<endl<<"\n\n\n";
	cout<<"Size requirement: product of row x col must be between 16 and 64 and be even "<<endl;


	cout<<"Enter rows:";
	cin>>row;
	cout<<"Enter columns:";
	cin>>col;

	product=row*col; //product of rows and columns
	cout<<"\n"<<endl;
	cout<<"Allowing 30 seconds per pair"<<endl;
	cout<<"You will have "<<(product/2*30) <<" seconds"<<endl;
	cout<<"Lets play"<<endl;

	time(&timer); /* get current time; same as: timer = time(NULL)  */

		seconds = difftime(timer, mktime(&y2k)); //difference of current time from the Jan 2000

//product should be 16 or more and 64 or less than it. Also only even numbers,otherwise it loops
	while(product%2 != 0 ||  product<16 || product>64) {
		cout<<"Size requirement: product of row x col must be between 16 and 64 and be even "<<endl;
		cout<<"Enter rows:";
		cin>>row;
		cout<<"Enter columns:";
		cin>>col;
		product=row*col;
	}


	int counter=0;
	for(int i=0; i<row;i++) {
		vector<int> temp;
		for(int j=0; j<col;j++) {


			if (counter>=(product/2)){
				temp.push_back(getRandomKeys(true));
			}else{
				temp.push_back(getRandomKeys(false));
				counter++;
			}
		}
		visibleboard.push_back(temp);
	}
	showBoard();

	int first, second;
	while (true) {

		cout << "Enter first slot to view : "; // ask user to guess the first slot
		cin >> first;
		while (first>product) //if unbounded
		{
			cout << "Enter first slot to view : ";
					cin >> first;
		}
		cout << "Enter second slot to view : ";
		cin >> second;
		while (second>product) //if unbounded
		{
					cout << "Enter second slot to view : ";
					cin >> second;
		}


		if (showBoardWithOptions(first, second)) {
			cout << "matched"<< endl;
			sleep(3);      //sleep after 3 seconds
			for(int i=0;i<100;i++)
						{
							cout<<endl;
						}


		}else {
			cout << "not matched"<< endl;
			sleep(3);
			for(int i=0;i<100;i++)
						{
							cout<<endl;
						}
			time(&now);   //current time
							sec = difftime(now, mktime(&y2k)); //current time - time of Jan as above
					         double difference=sec-seconds;

					         if(difference>(product/2)*30)//if time limits exceeds
					         {
					        	 cout<<"You exceeded "<<(product/2*30) <<" seconds"<<endl;

					        	 break;
					         }

		}
	}
	//after break
	cout<<"Time has expired"<<endl;
	cout<<"You revealed "<<endl;
	showBoardWithOptions(first, second);
	cout<<"All the pairs were at "<<endl;
	showBoard1(); //show the board that has character


}







