#include<iostream>
#include "Map.h"
using namespace std;

class MapV2 : public Map{
    private:
vector<Item*> itemVec;
    public:
MapV2(){
			ifderr = false;
			parser.tokenIt();

			nextToken = parser.getNext();

			if(nextToken == "<game>"){
				parser.eatToken();
				nextToken = parser.getNext();
				while(nextToken != "</game>"){  //consider what happens when run out of tokens && not error state
					if(nextToken == "<area>"){
						parser.eatToken();
						nextToken = parser.getNext();
						makeArea();
					}
					else if(nextToken == "<links>"){
						parser.eatToken();
						nextToken = parser.getNext();
						makeLinks();
					}
                    else if(nextToken == "<item>"){
						parser.eatToken();
						nextToken = parser.getNext();
						makeItem();
					}
					else{
						cout<<"Parse Error Location 1"<<endl;
						ifderr = true;
						break;
					}
					parser.eatToken();
					nextToken = parser.getNext();
				}// while !</game>

				if(ifderr){
					cout<<" :: ERROR :: IF Document Formatting Error"<<endl;
					cout<<"Game Loading Failed"<<endl;
					cout<<"General Area of Parsing Failure:"<<endl;
					cout<<"-------------------------------------"<<endl;
					cout<<nextToken<<endl;
					parser.eatToken();
					nextToken = parser.getNext();
					cout<<nextToken<<endl;
					parser.eatToken();
					nextToken = parser.getNext();
					cout<<nextToken<<endl;
					parser.eatToken();
					nextToken = parser.getNext();
					cout<<nextToken<<endl;
					cout<<"-------------------------------------"<<endl;
					return;
				}
				//cout<<"::Found </game>::"<<endl;
			}
			else{
				cout<<" :: ERROR :: No \"<game>\" tag found."<<endl;
				cout<<"Game Loading Failed"<<endl;
			}

			//link up areas
			linkLinks();


		//constructor
}

void makeItem(){
			string name, description;
            int room;
			string xstr;

			Item* tempItemPtr = new Item;

			while(nextToken != "</item>"){
				if(nextToken == "<desc>"){
					parser.eatToken();
					nextToken = parser.getNext();

					tempItemPtr->info.setDescription(nextToken);
				}
				else if(nextToken == "<name>"){
					parser.eatToken();
					nextToken = parser.getNext();

					istringstream ss(nextToken);
          				getline(ss, xstr, ',');
          				tempItemPtr->info.setID(atoi(xstr.c_str()));

          				getline(ss, xstr, ',');
					tempItemPtr->info.setGoal(atoi(xstr.c_str()));
				}
				else if(nextToken == "</desc>" || nextToken == "</feats>"){
				  //do nothing
				}
				else{
					cout<<"Parse Error Location 2"<<endl;
					ifderr = true;
					break;
				}

				parser.eatToken();
				nextToken = parser.getNext();
			}//while !</item>

			//add item to vector
			itemVec.push_back(tempItemPtr);

}









};