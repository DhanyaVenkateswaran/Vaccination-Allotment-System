#include <iostream>
#include <queue>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <string.h>

#define V 3
#define vacc 3
#define INFINITY 9999
#define l 10

using namespace std;

class vaccine{
public:
    string name,gender;
    int age,ano,area,uid;
    char vtype[100];
    int d1=0,m1=0,y1=0,d2=0,m2=0,y2=0;
    vaccine(){};
    vaccine(string n,string g ,int aad=0,int ar=0,int d=0,int m=0, int y=0,int dd=0, int mm=0, int yy=0,int a=0):name(n),gender(g),age(a),ano(aad),area(ar),d1(d),m1(m),y1(y),d2(dd),m2(mm),y2(yy){};
    void getdata(){
        string c;
        cout<<"Enter name, age, gender, aadhar number and area pincode"<<endl;
        cin>>name>>age>>gender>>ano>>area;
        cout<<"Have you taken dose 1? y-YES n-NO"<<endl;
        cin>>c;
        if (c=="y"){
            cout<<"Enter date of first dose and vaccine type"<<endl;
            cin>>d1>>m1>>y1>>vtype;
            cout<<"Have you taken dose 2? y-YES n-NO"<<endl;
            cin>>c;
            if (c=="y"){
                cout<<"Enter date of second dose "<<endl;
                cin>>d2>>m2>>y2;
            }
        }
        else{
            cout<<"Enter preferred vaccine type: covaxin or covishield or pfizer "<<endl;
            cin>>vtype;
        }
        cout<<"Data updated"<<endl;
    }
    void print(){
        cout<<uid<<"\t\t\t"<<name<<"\t\t\t"<<age<<"\t\t\t"<<gender<<"\t\t\t"<<ano<<"\t\t\t"<<area<<"\t\t\t"<<vtype<<endl;
    }
    void view(){
        cout<<endl;
        cout<<"DETAILS : "<<endl;
        cout<<endl;
        cout<<"User ID : "<<uid<<endl;
        cout<<"Name : "<<name<<endl;
        cout<<"Gender : "<<gender<<endl;
        cout<<"Age : "<<age<<endl;
        cout<<"Aadhar number : "<<ano<<endl;
        cout<<"Area pincode : "<<area<<endl;
        if (vtype != " "){
            cout << "First dose details" << endl;
            cout << "Vaccine type : " << vtype << endl;
            cout << "Date of first dose : " << d1 << "/" << m1 << "/" << y1 << endl;
            cout << "Second dose details" << endl;
            if ( d2 != 0 ){
                cout << "Date of second dose : " << d2 << "/" << m2 << "/" << y2 << endl;
            }
            else{
                cout << "YOU ARE YET TO TAKE THE SECOND DOSE "<<endl;
            }
        }
        else{
            cout << "YOU ARE YET TO TAKE BOTH THE DOSES "<<endl;
        }
    }
    friend bool operator < (vaccine a, vaccine  b);
};

bool operator < (vaccine a, vaccine  b)
{
    return ( a.age < b.age ? true : false);
}

class area{
    
    public :
        string hname;
        int ar, vac[3],vertex,d;
        static int knt; //
        int avl; // availability of hospital
        area(string h, int a):hname(h),ar(a){};
        area(){};
        
        void getdata()
        {
            vertex = knt++;
            if( avl == 0 )
                return;
            vac[0] = vac[1] = vac[2] = vacc;
            
        }
        
        void view()
        {
            if( avl == 0 )
                return;
            //if hospital is available then print area name
            cout<<"Hospital name : "<<hname<<endl;
            cout<<"Area : "<<ar<<endl;
            cout<<"Covaxin, covishield and pfizer daily dose count : "<<vac[0]<<"\t"<<vac[1]<<"\t"<<vac[2]<<endl;
        }
        void print(){
            cout<<"Area: "<<hname<<"\t"<<"Pincode: "<<ar<<endl;
        }
        void print1(){
                cout<<vertex<<"\t\t\t"<<hname<<"\t\t\t"<<ar<<"\t\t\t"<<vac[0]+vac[1]+vac[2]<<endl;
        }
    friend void dec(string name,int n);
        
};

int area::knt = 0;
area h[V];

int minDistance(int dist[], bool sptSet[])
{
   
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}

void bubbleSort(area arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j].d > arr[j + 1].d)
                swap(arr[j], arr[j + 1]);
}

void decvacno(string name,int n){
    for(int j=0;j<V;j++){
        if(h[j].hname==name){
            --h[j].vac[n];
        }
    }
}

// A utility function to print the constructed distance array
void printSolution(int dist[], int vac_no)
{
    cout <<"Finding closest vaccination centres : " << endl;
    int min = 1000,min_ID = 1000;
    area a[V];
    for ( int  i= 0; i< V; i++)
    {
        a[i] = area(h[i]);
        a[i].d = dist[i];
    }
    
    bubbleSort(a, V);
    for (int i = 0; i < V; i++)
    {
        if ( a[i].avl == 0 || a[i].vac[vac_no] < 0)
            continue;
        a[i].print();
        cout  <<"Distance is:" <<"\t"<<a[i].d<< endl<<endl;
        if( min > a[i].d )
        {
            min = a[i].d;
            min_ID = i;
        }
    }
    
    if( min == 1000 )
    {
        cout<<"There is no hospital available with the given\n";
        return;
    }
    cout<<"The hospital alloted for you is: \n";
    
    a[min_ID].print();
    cout  <<"Distance is:" <<"\t"<<a[min_ID].d<< "km "<< endl<<endl;
    string str=a[min_ID].hname;
    decvacno(str, vac_no);
}

 
void dijkstra(int graph[V][V], int src, int vac_no)
{
    int dist[V];
    bool sptSet[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    printSolution(dist, vac_no);
}


int main(){
    string hnames[] = { "Kodambakkam", "Meenambakkam", "Nungambakkam",};
    int avls[] = {1, 0, 1}, areas[] = {34,33,72};
    

    for ( int i = 0; i < V ; i ++)
    {
        h[i].ar = areas[i];
        h[i].hname = hnames[i];
        h[i].avl = avls[i];
        h[i].getdata();
    }
    
    int graph[V][V] = { { 0, 5, 0 },
                        { 5, 0, 4},
                        { 0, 4, 0} };
    
    vaccine a[5];
    
    char v1[]="covaxin",v2[]="covishield",v3[]="pfizer";
        for (int i =0; i<5; i++){
            a[i].uid=i;
            a[i].getdata();
        }
        priority_queue <vaccine> pq;
        for (int i=0;i<5;i++){
            pq.push(a[i]);
        }
        while (pq.empty() == false){
            int k=0;
            vaccine temp= pq.top();
            cout<<"Hello "<<temp.name<<endl<<endl;
                for(int j=0;j<V;j++)
                {
                    if(temp.d2!=0){
                        cout<<"You have already been vaccinated twice."<<endl;
                        break;
                    }
                    if(temp.area==h[j].ar){
                        k=1;
                            if(strcmp(temp.vtype,v1)==0)
                                dijkstra(graph, h[j].vertex,0);
                            
                            else if(strcmp(temp.vtype,v2)==0)
                                dijkstra(graph, h[j].vertex,1);
                            
                            else if(strcmp(temp.vtype,v3)==0)
                                dijkstra(graph, h[j].vertex,2);
                            
                            else
                                cout<<"Invalid choice"<<endl;
    
                }
                    for (int i=0;i<5;i++){
                        if(temp.name==a[i].name){
                            if (a[i].d1==0){
                                a[i].d1=24;
                                a[i].m1=6;
                                a[i].y1=2022;
                                break;
                            }
                            else if(a[i].d1!=24 and a[i].m1!=6 and a[i].y2!=2022){
                                a[i].d2=24;
                                a[i].m2=6;
                                a[i].y2=2022;
                                break;
                            }
                            
                        }
                    }
                }
            if(k==0 and temp.d2==0){
                cout<<"There are no active vaccination centres near you. Kindly wait "<<endl;
            }
                pq.pop();
   
            }
    
        int choice;
        do{
            cout<<"Enter choice \n1 - to view all patient data \n2 -to to view all dose availability \n3 -to search for patient and view details \n4 - to search for hospital and view details \n5 - to exit"<<endl;
            cin>>choice;
            switch(choice){
                case 1:{
                    cout<<"USER ID"<<"\t\t"<<"NAME"<<"\t\t"<<"AGE"<<"\t\t"<<"GENDER"<<"\t\t"<<"AADHAR NO."<<"\t\t"<<"AREA CODE"<<"\t\t"<<"VACCINE TYPE"<<endl;
                    for (int i =0; i<5; i++){
                        a[i].print();
                    }
                    break;
                }
                case 2:{
                    cout<<"S NO."<<"\t"<<"VACCINATION CENTRE AREA"<<"\t\t"<<"AREA CODE"<<"\t\t"<<"AVAILABLE DOSE COUNT"<<endl;
                    for (int i =0; i<3; i++){
                        h[i].print1();
                    }
                    break;
                }
                case 3:{
                    int u;
                    cout<<"Enter user id "<<endl;
                    cin>>u;
                    for (int i =0; i<5; i++){
                        if(a[i].uid==u){
                            a[i].view();
                        }
                    }
                    break;
                }
                case 4:{
                    int h1;
                    cout<<"Enter hospital id "<<endl;
                    cin>>h1;
                    for (int i =0; i<3; i++){
                        if(h[i].vertex==h1){
                            h[i].view();
                        }
                    }
                    break;
                }
                default:{
                    cout<<"Ending program .. Thank you!"<<endl;
                    break;
                }
            }
        } while (choice!=5);
    
    return 0;
}
