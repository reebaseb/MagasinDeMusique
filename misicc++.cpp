#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include <string.h>

using namespace std;

int col =15 , row =0 ,flag=0;

COORD coord = {0,0};

void gotoxy(int x,int y)
{
	 COORD coord;
	 
	 coord.X =x;
	 coord.Y = y;
	 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	 
}
	 
 ofstream fout;
 ifstream fin;
	 
	 
class MusicItem
{
	int ID;
	char Category[10];
	char Genre[10];
	char Name[100];
	char Artist[100];
	//string Name;  /* to read more the 2 words */
	//string Artist;

	

            public:
		void additem()
		{
		        cout<<"\n\t Item ID: ";
		        cin>>ID;
		        cout<<"\n\t Category (Old/New): ";
		        cin>>Category;
		        cout<<"\n\t Genre (Pop/Rock/Jazz/Country,etc): ";
		        cin>>Genre;
		        cout<<"\n\t Name of Song:";
		        cin.get();     /* to make it to wait to read */
		        //cin>>Name;
		       gets(Name);        /* read name */
		        cout<<"\n\t Artist: " ;
		        gets(Artist);
				//cin>>Artist;		
		}
		
	
     	void header()
	    {
	       cout<<"\n\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n ";
	       cout<<"\n\t\t MUSIC RECORD DETAILS ";
            cout<<"\n\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n\n";	
        }

	void showitem()
	{
				
			cout<<"\n\t Item ID      :" <<ID;
			cout<<"\n\t Category     :"<<Category ;
			cout<<"\n\t Genre        :"<<Genre;  
			cout<<"\n\t Name of Song :";
                               puts(Name);
                               //cout<<Name;
			cout<<"\t Artist       :";
                              puts(Artist);
							  //cout<<Artist;	
	}
		
	void printitem()
	{
			gotoxy(5,col);
			cout<<ID;
			gotoxy(15,col);
			puts(Category);
			gotoxy(30,col);
			puts(Genre);
			gotoxy(45,col);
	    	          cout<<Name;
			gotoxy(60,col);
			cout<<Artist;
			
	}
		
	int retID()
	{
		return(ID);
	}
				
         string retCategory()
	{
		return(Category);
	}
		
         string retGenre()
	{
		return(Genre);
	}
	
	string retName()
	{
		return(Name);
	}
	
	string retArtist()
	{
		return(Artist);
	}
		
		
};


class OrderItem:public MusicItem
{
		int Qty;
		int Price;
		int GST;
		int gross;
		int netamt;
	
	

               public:
		void additem();
		void edititem();
		void showitem();
		void showallitems();
		void deleteitem();
		void printitem();
		void calculate_netamt();
		void showoutput();
		
		int retnetamt()
		{
			return(netamt);
		}
		
       }order;

void OrderItem::additem()
{
	MusicItem::additem();
	
	cout<<"\n\t Quantity : ";
	cin>>Qty;
		
	cout<<"\n\t Price : ";
	cin>>Price; 
		
	cout<<"\n\t GST percent : ";
	cin>>GST; 
		
	calculate_netamt();
    
	fout.write((char *)&order,sizeof(order));
	fout.close();
		
} /* end of add item */



void OrderItem::edititem() 
{
	
          fstream temp("temp.dat",ios::app);	
    
	MusicItem::additem();
	
	cout<<"\n\t Quantity : ";
	cin>>Qty;
		
	cout<<"\n\t Price : ";
	cin>>Price; 
		
	cout<<"\n\t GST percent : ";
	cin>>GST; 
		
	calculate_netamt();
    
	temp.write((char *)&order,sizeof(order));
	temp.close();
		
   }


    void OrderItem::calculate_netamt()
    {
          gross= Price + (Price * (GST/100)) ;
          netamt= Qty * gross; 
     }


    void OrderItem::showitem()
    {
	MusicItem::showitem();
    }

   
  void OrderItem::deleteitem()
     {
               int id;
   	
	     fstream temp("temp.dat",ios::out);
               if (fin.fail())
	      {
		cout<<"\n\n FILE NOT FOUND.....";
	       }
	      fin.seekg(0);	 
   	      cout<<"\n\n\t Enter the Item ID to be deleted : ";
  	      cin>>id;
   
                while(fin.read((char*)&order,sizeof(order)));
                  {
                     	int x= order.MusicItem::retID();
                 
                  	          if (x!=id)
                               {
			        temp.write((char *)&order,sizeof(order));
		            }
			 else
			        flag =1; 
                  }/* end of while */
		  	
	    fin.close();
	    temp.close();
			 
	    fout.open("MusicItemStore.dat", ios::trunc);
              fout.seekp(0);
               temp.open("temp.dat",ios::in);
		 		 
	    if(!temp)
	  {
		cout<< "Error ....temp file";
	    }
	/* read from temp file and write to MusicStore.dat*/	
            	while(temp.read((char *)&order,sizeof(order)))
			           fout.write((char *)&order,sizeof(order));
			     
			     
			     
	      temp.close();
	      fout.close();
			
	      if (flag ==1)
		   cout<<"\n\n Item Deleted Successfully.....";
	     else if (flag ==0)
	            cout<< "\n\t\t  Item does not Exist... Try again";
	} /* end of deleteitem*/



void OrderItem::printitem()
{
	
	MusicItem::printitem();
	gotoxy(75,col);
	cout<<Qty;
	
	gotoxy(95,col);
	cout<<Price;
	
	gotoxy(110,col);
	cout<<GST;
		
	gotoxy(120,col);
	cout<<netamt;
	
	col=col+1;
	
	if(col==50)
	{
		
		gotoxy(25,50);
		cout<<"PRESS ANY KEY TO CONTINUE....";
		getch();
		col=10;
		system("cls");
		gotoxy(30,2);
		cout<< " MUSIC RECORD DETAILS";
		gotoxy(5,5);
		cout<<"ITEM ID";
		gotoxy(15,5);
		cout<<"CATEGORY";
		gotoxy(30,5);
		cout<<"GENRE";
		gotoxy(35,5);
		cout<<"NAME OF SONG";
		gotoxy(45,5);
		cout<<"ARTIST";
		gotoxy(55,5);
		cout<<"QUANTITY";
		gotoxy(65,5);
		cout<<"PRICE";
		gotoxy(75,5);
		cout<<"GST";
		gotoxy(85,5);
		cout<<"GROSS";
		gotoxy(95,5);
		cout<<"NET AMOUNT";
		
	}
}

void OrderItem::showoutput()
{
	showitem();
         cout<<"\n\t QUANTITY    :"<<Qty;
		 cout<<"\n\t PRICE       :"<<Price ;
		 cout<<"\n\t GST         :"<<GST;  
		 cout<<"\n\t GR          :"<<gross;
		 cout<<"\n\t NET Amount  :"<<netamt ;	
        cout<<"\n  _____________________________________________________ ";

}

void OrderItem::showallitems()
{
        
	   fin.open("MusicItemStore.dat",ios::binary|ios::in);
				
		if (!fin)		
		 {
		   	cout<<"\n\n\t File not found.....";
		 //   goto menu;
		 }
		 fin.seekg(0);
		 cout<<"\n--------   ALL ITEMS DETAILS   --------";
	           cout<<"\n  __________________________________________ ";

		 while(fin.read((char *)&order, sizeof(order)))
				{
				  
					order.showoutput();  /* display all item details*/
				
				}
		fin.close();	
   } /* end of showallitems */




int main()
{
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout<<setprecision(2);

	fstream temp("temp.dat",ios::out);
	
           time_t my_time = time(NULL);   /* to show date and time in bill*/
  
	



      menu:
		
		int choice;
		float gtotal;
		int id, flag=0,qty;
		int want=1;
		int ff;
		string category=" ";
	          string genre =" ";
	          char name[20];
		char artist[20];


									 	  
		system("cls");
		gotoxy(25,4);
		cout<<"\n\t\t      Welcome to \"MAGASIN DE MUSIQUE\"     ";
		gotoxy(25,5);
		cout<<"\n\n\t\t #########################################\n\n";
		cout<<"\n\t  1. Add New Item\n";
		cout<<"\n\t  2. Delete\\Remove Item\n";
		cout<<"\n\t  3. Edit Item \n";
		cout<<"\n\t  4. Show  Item\n";
		cout<<"\n\t  5. Find Music Item by (Id/Category/Name/Type/Artist)\n";
		cout<<"\n\t  6. Bill Report \n";
		cout<<"\n\t  7. Exit \n\n";
		cout<<"\t\t Enter your option:";
		cin>>choice;
		
	
	    switch(choice)
	    {
	    	case 1: /* Add New Item */
	    	
	               system("cls");
		     gotoxy(10,10);
		     cout<<"\n\t\t      Welcome to \"MAGASIN DE MUSIQUE\"     ";
		     cout<<"\n\t\t ****************************************** \n";
		    
		     cout<<"\n\t\t\t--------  Add Item  ---------\n";   	
		         fout.open("MusicItemStore.dat", ios::app); 	
                              order.additem();
	   	          cout<<"\n\t\t Item Added Successfully !!! ";
		          getch();
		          goto menu;
				  
	            case 2:   /* Delete item */
				   
			  system("cls");
			  cout<<"\n\t\t       Welcome to \"MAGASIN DE MUSIQUE\"     ";
			  cout<<"\n\t\t*************************************** \n";
			  cout<<"\n\t\t\t...... Delete Item.......\n";
			  
			  order.showallitems();
		            fin.open("MusicItemStore.dat", ios::in);
			  order.deleteitem();
			  getch();
			
			  goto menu;
					
		case 3: 
    	 	            system("cls");
		            cout<<"\n\t\t   Welcome to \"MAGASIN DE MUSIQUE\"     ";
		            cout<<"\n\t\t*************************************** \n";
		            cout<<"\n\t\t\t...... Edit Item ......\n";
  		            order.showallitems();
			  cout<<"\n\n\t Enter Item Id to be edited : ";
			  cin>>id;
				
			  
                              fin.open("MusicItemStore.dat",ios::binary|ios::in);
				
		  	if (!fin)		
			     {
			     	cout<<"\n\n\t File not found.....";
				 goto menu;
  			     }
						 
	   	



                        fin.seekg(0);
	              while(fin.read((char *)&order, sizeof(order)))
		    {
			int x=order.MusicItem::retID();
					
			if (x==id)
			{
				order.showoutput();  /* display the particular item details*/
				flag =1;
					
			} 
			if (x!=id)  /* if not equal copy record to temp file*/
                                    temp.write((char *)&order, sizeof(order));

  		     }
				
	  	     if (flag ==0)
	 	     {
			  cout<< "\n\t\t  Item does not Exists... Try again";
		     }
				
		     fin.close();
		     temp.close();
				
	
				
				
/* to edit the item and add as new	*/
  	 cout<<" \n\nEnter new data.... Please keep Item ID same... Edit other attributes";	 order.edititem();
			 	 	
	 fout.open("MusicItemStore.dat", ios::trunc);
	 fout.seekp(0);
	 temp.open("temp.dat",ios::in);  /* open temp file for reading*/
	 


            	  if(!temp)
	   	 {
	    		  cout<< "Error.... temp file";
	  	  }
			 
	   	 while(temp.read((char *)&order,sizeof(order)))
	  	  {
	    		 fout.write((char *)&order,sizeof(order));
	  	  }
	  	  temp.close();
	  	  fout.close();	 
				 	 
	 	   cout<<"\n\t\t Item Edited Successfully !!! ";
	 	   getch();
			
	 	   goto menu;
	    	
	case 4:  
		
		 system("cls");
		 cout<<"\n\n\t\t        Welcome to \"MAGASIN DE MUSIQUE\"    ";
		cout<<"\n\n\t\t  *********************************** \n";
		cout<<"\n\n\t ....... Show All Items......\n";
			      
		order.showallitems(); /* display all items */
		cout<<"\n\n\t  ***************************************** ";	
		cout<<"\n\t\t SEARCH FOR PARTICULAR ITEM DETAILS  \n"	;
		cout<<"\n\n\t  ***************************************** \n";		
		cout<<"\n\n\t Enter Item Id to be shown : ";
		cin>>id;
				
		fin.open("MusicItemStore.dat",ios::binary|ios::in);
				
		if (!fin)		
		 {
                         cout<<"\n\n\t File not found.....";
		      goto menu;
		 }
				 	
	   	    fin.seekg(0);  /* goes to first record*/
		    fin.read((char *)&order, sizeof(order));
		    while(!fin.eof())
			{
				int x=order.MusicItem::retID();
				if (x==id)
				{
					order.showoutput();
					flag =1;
					break;
			           }
                                         fin.read((char *)&order, sizeof(order));

			}/* end of file*/
				
			if (flag ==0)
			{
				cout<< "\n\t\t  Item does not Exist... Try again";
			}
				
			getch();
			fin.close();
			goto menu;
					
		case 5:
								
		     int ch;
		     
		     system("cls");
	               cout<<"\n\n\t\t        Welcome to \"MAGASIN DE MUSIQUE\"     ";
	               cout<<"\n\n\t\t  *********************************** ";
			      
   		     cout<<"\n\n\t Find item (id/category/name/genre) ";
   			 			      
			  cout<<"  \n\n                    1: Id";
			  cout<<"  \n\n                    2: Category";
			  cout<<"  \n\n                    3: Genre";
			  cout<<"  \n\n                    4: Name";	  	
			  cout<<"  \n\n                    5: Artist\n";
		  	  cout<<"\n\nEnter your choice :"; 
			  cin>>ch;




		

                   switch(ch)  
		  {
				   case 1:				 				
				          cout<<"\n\n\t Enter Music Id : ";
				          cin>>id;
				          goto op;
				         
				    case 2:
				    	 cout<<"\n\n\t Enter Music Category : ";
				          cin>>category;
				          goto op;
				         
				    case 3:
				    	cout<<"\n\n\t Enter Music Type : ";
				          cin>>genre;
				          goto op;
				       
				    case 4:
					     cout<<"\n\n\t Enter Music name : ";
				          cin>>name;
				          goto op;
				          
				    case 5:
				    	cout<<"\n\n\t Enter Music Artist: ";
				          cin>>artist;
				          goto op;
				         
									          
			     op:	
			     	fin.open("MusicItemStore.dat",ios::binary|ios::in);
				
			    	if (!fin)		
			          { 
                                                     cout<<"\n\n\t File not found.....";
				      goto menu;
				 }
				/* print header	 **/		 
			       order.header();
			    






                                    fin.seekg(0);
			      while(fin.read((char *)&order, sizeof(order)))
				  {
					int x=order.MusicItem::retID();
					string  c=order.MusicItem::retCategory();
					string t =order.MusicItem::retGenre();
					string n=order.MusicItem::retName();
					string a=order.MusicItem::retArtist();
					
					if (x==id)
					{
												
						order.showoutput();
						flag =1;
						break;
					}
					if ((c.compare(category)) == 0)
					{
					
						cout<<"category"<<category;
						order.showoutput();
						flag =1;
						break;
					}
					
					if ((t.compare(genre)) == 0)
					{
						
						order.showoutput();
						flag =1;
						break;
					}
					
					if ((n.compare(name)) == 0)
					{
					
						order.showoutput();
						flag =1;
						break;
					}
					   




                                                  if ((a.compare(artist)) == 0)
					{
					
						order.showoutput();
						flag =1;
						break;
					}
			 	  }
				
				     if (flag ==0)
				     {
				    	cout<< "\n\t\t  Item does not Exists... Try again";
			     		
				      }
		 	        }
				  getch();
			  	  fin.close();
			  	  goto menu;
   			   
   			    		
	            case 6:
			    
		  bill: 
		        system("cls");
	            cout<<"\n\n\t\t\t     Welcome to \"MAGASIN DE MUSIQUE\"    ";
		        cout<<"\n\n\t\t\t  ************************************** ";
   		        cout<<"\n\n Generate Bill ";
   		        cout<<"\n_________________________________________\n";
						 
			 /* GENERATE BILL*/
					 	    
					 	  					 	   
			  cout<<" \n\n\t....... TAX INVOICE/ BILL OF SUPPLY .......\n";
			  //order.header();
			  cout<<"\n";
					 	    					 	     
			  gotoxy(5,11);
			  cout<<"MUSIC_ID";
			  gotoxy(15,11);
			  cout<<"CATEGORY";
			  gotoxy(30,11);
			 cout<<"GENRE";
			 	gotoxy(45,11);
			    cout<<"NAME OF SONG";
			    gotoxy(60,11);
			    cout<<"ARTIST";
			    gotoxy(75,11);
			    cout<<"QUANTITY";
			    gotoxy(95,11);
			    cout<<"PRICE";
			    gotoxy(110,11);
			    cout<<"GST";
			    gotoxy(125,11);
			    cout<<"NET AMOUNT";
			   cout<<"\n __________________________________________________________________________________________________________________________________";
					 	     
	           fin.open("MusicItemStore.dat",ios::in);
		  if(fin.fail())
		   {
		     	cout<<"\n\n File not found";
			goto menu;
		  }
		 
                      fin.seekg(0);
		 while(!fin.eof())
		 {
			fin.read((char *)&order, sizeof(order));
			if (!fin.eof())
			{
				order.printitem();
				gtotal+=order.retnetamt();
				ff=0;
				 		
			 }
				 if(ff!=0)
				    gtotal=0;
		}
				 		
			
		 		 gotoxy(90,col);
			 	cout<<"\n -----------------------------------------------------------------------------------------------------------------------------------";
 cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t GRAND TOTAL  Rs.= "<<gtotal;
	  	cout<<"\n -----------------------------------------------------------------------------------------------------------------------------------\n\n\n";
	cout<<"\n\n\n....THANK YOU \n";				
	cout <<"For shopping  with \"MAGASIN DE MUSIQUE\"  \n\n";
							   
    	// ctime() used to give the present time 
     	   printf("%s", ctime(&my_time)); 
	 getch();
	 fin.close();
           fout.open("MusicItemStore.dat", ios::trunc); /*  cart for next customer */
           fout.close();
			
 


	   case 7:
		 cout<<"\n\n \t Do you wish to Exit (y/n)";
		 char yn;
		 cin>>yn;
				 
		 if ((yn=='Y') || (yn=='y'))
		 {
		 	exit(0);
		 }
		 else if ((yn=='N') || (yn=='n'))
			goto menu;
					
		 else 
		         goto menu;
				   
			
	   default:
	 	cout<<"\n\n\t\t Wrong Choice ... Enter the right Choice....";
		getch();
			
		goto menu;
				
	}/*end of main switch */
}/* end of main*/
