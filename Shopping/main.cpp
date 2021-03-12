#include <iostream>
#include<fstream>
#include<stdio.h>
#include<string.h>
void displaybill(int billno);
using namespace std;
class products
{
public:
    char pname[100];
    int   pid;
    float price;
    void accept()
    {
        cout<<endl<<"Enter Product ID: ";
        cin>>pid;
        fflush(stdin);
        cout<<"Enter Product Name: ";
        gets(pname);
        cout<<"Enter Product Price: ";
        cin>>price;
    }
    void display()
    {
        cout<<endl;
        cout<<"Product Name: "<<pname<<endl;
        cout<<"Product ID: "<<pid<<endl;
        cout<<"Product Price: "<<price<<endl;
    }
};
products pobj;
class bill
{
public:
    int billno;
    char date[20];
    int pid;
    char pname[100];
    float price;
    void accept()
    {
        cout<<"Enter Bill No.";
        cin>>billno;
        fflush(stdin);
        cout<<"Enter Bill Date";
        cin>>date;
    }
    void display(int srno)
    {
        cout<<"\t\t\t"<<srno<<"\t";
        cout<<pid<<"\t";
        cout<<pname;
        for(int i=1; i<=15-strlen(pname); i++)
        {
            cout<<" ";
        }
        cout<<price<<endl;
    }
};
bill billobj;
void generatebill()
{
    fstream rd("products.txt",ios::in);

    if(!rd)
    {
        cout<<" ERROR OPENING FILES "<<endl;
    }
    else
    {
        float total=0;
        int scancode;
        int e=1;
        int n;
        int flag;
        billobj.accept();
        rd.seekg(0,ios::end);
        n = rd.tellg()/sizeof(pobj);
        rd.seekg(0,ios::beg);
        while(e)
        {
            rd.seekg(0,ios::beg);
            flag =0;
            fflush(stdin);
            cout<<"Enter scan code (0 for exit) :";
            cin>>scancode;
            if(scancode==0)
            {
                e = 0;
            }
            else
            {
                for(int i=1; i<=n; i++)
                {
                    rd.read((char*)&pobj,sizeof(pobj));
                    if(pobj.pid==scancode)
                    {
                        flag = 1;
                        pobj.display();
                        billobj.pid = pobj.pid;
                        strcpy(billobj.pname,pobj.pname);
                        billobj.price = pobj.price;
                        total += pobj.price;
                        cout<<"Total bill is = "<<total<<endl;
                        break;
                    }
                }

                if(flag==1)
                {
                    fstream wr("bills.txt",ios::app);
                    wr.write((char*)&billobj,sizeof(billobj));
                    wr.close();
                }
                else
                {
                    cout<<endl<<"INVALID SCAN CODE"<<endl;
                }
            }
        }
        cout<<endl<<"!!!BILL GENERATED SUCCESSFULLY!!!"<<endl;
        rd.close();
        displaybill(billobj.billno);
    }
}
void displaybill(int billno)
{
    fstream rd;
    rd.open("bills.txt",ios::in);
    if(!rd)
        cout<<endl<<"ERROR OPENING FILE"<<endl;
    else
    {
        int n;
        float total=0;
        rd.seekg(0,ios::end);
        n = rd.tellg()/sizeof(billobj);
        rd.seekg(0,ios::beg);
        cout<<endl<<"\t\t\t"<<"WELCOME TO TRILIUM MALL ";
        cout<<endl<<"\t\t\t"<<"Bill No. "<<billno;
        cout<<endl<<"\t\t\t"<<"Sr No."<<"\t"<<"Pid"<<"\t"<<"Pname"<<"\t\t"<<"Price"<<endl;
        int srno=0;
        for(int i=1; i<=n; i++)
        {
            rd.read((char*)&billobj,sizeof(billobj));
            if(billobj.billno == billno)
            {
                srno++;
                billobj.display(srno);
                total+= billobj.price;
            }
        }
        cout<<endl<<"\t\t\t"<<" TOTAL BILL "<<total;
        cout<<endl<<" THANKS FOR SHOPPING "<<endl;
        rd.close();
    }
}
void dailysale()
{
    fstream rd;
    rd.open("bills.txt",ios::in);
    if(!rd)
        cout<<" ERROR OPENING FILE "<<endl;
    else
    {
        char saledate[20];
        cout<<"Enter date of sale :";
        cin>>saledate;
        int n;
        float total=0;
        rd.seekg(0,ios::end);
        n = rd.tellg()/sizeof(billobj);
        rd.seekg(0,ios::beg);
        cout<<endl<<"\t\t\t"<<"Daily Sale For :  "<<saledate;
        cout<<endl<<"\t\t\t"<<"BILL NO"<<"\t\t"<<"PID"<<"\t"<<"PNAME"<<"\t\t"<<"PRICE";
        for(int i=1; i<=n; i++)
        {
            rd.read((char*)&billobj,sizeof(billobj));
            if(strcmp(billobj.date,saledate)==0)
            {
                cout<<endl<<"\t\t\t"<<billobj.billno;
                cout<<"\t"<<billobj.pid;
                cout<<"\t"<<billobj.pname;
                cout<<"\t"<<billobj.price;
                total+= billobj.price;
            }
        }
        cout<<endl<<"\t\t\t"<<" TOTAL SALE "<<total<<endl;
        rd.close();
    }

}
void addproduct()
{
    fstream wr("products.txt",ios::app);
    if(!wr)
        cout<<"ERROR CREATING FILE";
    else
    {
        pobj.accept();
        wr.write((char*)&pobj,sizeof(pobj));
        cout<<endl<<"!!!PRODUCT ADDED SUCCESSFULLY!!!";
        cout<<endl;
        wr.close();

    }
}
void viewallproducts()
{
    fstream rd("products.txt",ios::in);
    if(!rd)
        cout<<"ERROR SEARCHING FILE";
    else
    {
        int n;
        rd.seekg(0,ios::end);
        n=rd.tellg()/sizeof(pobj);
        rd.seekg(0,ios::beg);
        for(int i=1; i<=n; i++)
        {
            rd.read((char*)&pobj,sizeof(pobj));
            pobj.display();
            cout<<"*********************";
        }
        rd.close();
    }
}
void deleteproducts()
{
    fstream rd("products.txt",ios::in);
    fstream wr("temp.txt",ios::app);
    if(!rd||!wr)
        cout<<"ERROR OPENING FILES";
    else
    {
        int n;
        int id;
        int flag=0;
        cout<<"Enter Product ID: ";
        cin>>id;
        rd.seekg(0,ios::end);
        n=rd.tellg()/sizeof(pobj);
        rd.seekg(0,ios::beg);
        for(int i=1; i<=n; i++)
        {
            rd.read((char*)&pobj,sizeof(pobj));
            if(id!=pobj.pid)
            {
                wr.write((char*)&pobj,sizeof(pobj));
            }
            else
            {
                flag=1;
            }
        }
        rd.close();
        wr.close();
        remove("products.txt");
        rename("temp.txt","products.txt");
        if(flag==0)
            cout<<"PRODUCT NOT FOUND"<<endl;
        else
            cout<<endl<<"!!!PRODUCT DELETED SUCCESSFULLY!!!"<<endl;

    }
}
void updateproducts()
{
    fstream rd;
    fstream wr;
    rd.open("products.txt",ios::in);
    wr.open("temp.txt",ios::app);
    if(!rd||!wr)
        cout<<"ERROR OPENING FILES";
    else
    {
        int id;
        int flag=0;
        int n;
        cout<<"Enter PID to update";
        cin>>id;
        rd.seekg(0,ios::end);
        n=rd.tellg()/sizeof(pobj);
        rd.seekg(0,ios::beg);
        for(int i; i<=n; i++)
        {
            rd.read((char*)&pobj,sizeof(pobj));
            if(pobj.pid==id)
            {
                cout<<"Enter product details";
                pobj.accept();
                wr.write((char*)&pobj,sizeof(pobj));
                flag=1;

            }
            else
            {
                wr.write((char*)&pobj,sizeof(pobj));

            }
        }
        rd.close();
        wr.close();

        remove("products.txt");
        rename("temp.txt","products.txt");
        if(flag==0)
            cout<<"Product  not found";
        else
            cout<<endl<<"!!!PRODUCT UPDATED SUCCESSFULLY!!!"<<endl;
    }

}
void searchproducts()

{
    fstream rd("products.txt",ios::in);
    if(!rd)
        cout<<"ERROR OPENING FILE";
    else
    {
        int n;
        int id;
        int flag=0;
        cout<<"Enter Product ID To Search: ";
        cin>>id;
        rd.seekg(0,ios::end);
        n=rd.tellg()/sizeof(pobj);
        rd.seekg(0,ios::beg);
        for(int i; i<=n; i++)
        {
            rd.read((char*)&pobj,sizeof(pobj));
            if(pobj.pid==id)
            {
                flag=1;
                pobj.display();
                cout<<"********************"<<endl;
                break;
            }
        }

        rd.close();
        if(flag==0)
            cout<<endl<<"PRODUCT NOT FOUND"<<endl;
    }
}



main()
{
    int choice;
    int e=1;
    do
    {
        cout<<endl;
        cout<<"Enter 1 To Add Products"<<endl;
        cout<<"Enter 2 To View Products"<<endl;
        cout<<"Enter 3 To Delete Products"<<endl;
        cout<<"Enter 4 To Update Products"<<endl;
        cout<<"Enter 5 To Search Products"<<endl;
        cout<<"Enter 6 To Generate Bill"<<endl;
        cout<<"Enter 7 To View Sales"<<endl;
        cout<<"Enter 8 To Exit"<<endl;
        cout<<"ENTER YOUR CHOICE: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            addproduct();
            break;
        case 2:
            viewallproducts();
            break;
        case 3:
            deleteproducts();
            break;
        case 4:
            updateproducts();
            break;
        case 5:
            searchproducts();
            break;
        case 6:
            generatebill();
            break;
        case 7:
            dailysale();
            break;
        case 8:
            e=0;
            break;
        default:
            cout<<"---INVALID CHOICE---";
        }
    }
    while(e);

}
