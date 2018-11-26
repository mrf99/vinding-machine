#include <iostream>
#include <cstdlib>
using namespace std;

class Client ///This class deals with the client
{
protected:
    double user_quant_money; ///Quantity of money
    double user_kind_of_money; ///Type of money
    int quant_20=0,quant_10=0,quant_5=0,quant_1=0,quant_05=0; ///Quantity of each type
    double all_money; ///Money as a whole is equal user_quant_money * user_kind_of_money
    string user_type; ///The name of the client request
    double user_quantity; ///Customer request number
public:
    Client()
    {}
    friend istream&operator>>(istream &in,Client&vend); ///We take from the customer the name of the product and the number and money
};
class In_Vending_Machine :public Client ///In this class there is the name, number and price of the products and the money in vending machine
{
private:
    string name[10]= {"pepsi","chipsy","choclete","juice","cafe","jum","endomy","merenda","cake","icecream"}; ///Product Names
    int quantity[10]= {10,10,10,10,10,10,10,10,10,10}; ///Number of products
    double price[10]= {5,5,5,4.5,2.5,.5,3.5,5,2,10}; ///Products prices
    int money_in_machine_quantity[5]= {50,100,100,100,100};/// Money in vending machine .5 1 5 10 20
    int user_choice=0; ///Customer index Number (Product Name)
    double total_price=0; ///Product price * Product number
    double user_money; ///The change of the client's money

public:
    In_Vending_Machine()
    {
    }
    void print() ///will print the name, number, and price of the product
    {
        for (int j=0; j<10; j++)
        {
            cout<<"item "<<j+1<<" "<<name[j]<<"  price: "<<price[j]<<"  quantity: "<<quantity[j]<<endl;
        }
    }
    bool check_all()///Make sure that the name and number of the product and that the price is equal to or greater than the price of the product
    {
        bool check_type=false,check_quant=false,check_money=false;
        for(int i=0; i<10; i++)
        {
            if (user_type==name[i]) ///Look for the product type in the machine
            {
                user_choice=i;
                check_type=true;
                break;
            }
        }
        if (!check_type) ///Make sure you have the product name
            cout<<"wrong type"<<endl;
        if (quantity[user_choice]>=user_quantity)
            check_quant=true;                       ///Make sure you have the quantity that the customer wants
        if (quantity[user_choice]<user_quantity&&check_type)
            cout<<"no enough quantity the quantity is: "<<quantity[user_choice]<<endl;
        if (user_quantity<0) ///are sure he does not want the amount of 0
        {
            cout<<"quantity <0!"<<endl;
            check_quant=false;
        }
        if (check_type&&check_quant) ///If the name and the number are correct, we calculate and verify the money
        {
            total_price=user_quantity*price[user_choice];
            if (total_price<=all_money||total_price<=user_money)
            {
                user_money+=all_money;
                check_money=true;
            }
            if (user_money<total_price||user_quant_money<0)
            {
                cout<<"u didn't put enough money\ntake ur money from machine!"<<endl;
                user_money-=all_money;
                check_money=false;
            }
        }
        if (check_type&&check_quant&&check_money)///If all is true return true
        {
            return true;
        }
    }
    void save_money() ///collect the number of coins with the number of coins in vending machine from each category
    {
        money_in_machine_quantity[0]+=quant_05; ///It collects the number of coins in the category of 0.5
        money_in_machine_quantity[1]+=quant_1; ///It collects the number of coins in the category of 1
        money_in_machine_quantity[2]+=quant_5; ///It collects the number of coins in the category of 5
        money_in_machine_quantity[3]+=quant_10; ///It collects the number of coins in the category of 10
        money_in_machine_quantity[4]+=quant_20; ///It collects the number of coins in the category of 20
    }
    void change() ///print the change of the money to the customer
    {
        double temp=0,temp1=0; /// temp for Total client's money  temp1 for Number of coins of each category
        int count=0; ///Number of coins of each category
        user_money-=total_price; ///The change of the client's money
        temp=user_money;
        while(temp>=20)///count the coins number of the category 20
        {
            temp-=20;
            count++;
        }
        temp1=count;
        cout<<"ur charge is: ";
        for (; count>=0; count--)
        {
            if (money_in_machine_quantity[4]-count>0)
            {
                money_in_machine_quantity[4]-=count;
                break;
            }
        }
        cout<<"20*"<<count<<" ";
        count-=temp1;
        count*=2;
        while(temp>=10) ///count the coins number of the category 10
        {
            temp-=10;
            count++;
        }
        temp1=count;
        for (; count>=0; count--)///confirm the number of coins in the machine
        {
            if (money_in_machine_quantity[3]-count>0)
            {
                money_in_machine_quantity[3]-=count;
                break;
            }
        }
        cout<<"10*"<<count<<" ";
        count-=temp1;
        count*=2;
        while(temp>=5) ///count the coins number of the category 5
        {
            temp-=5;
            count++;
        }
        temp1=count;
        for (; count>=0; count--)///confirm the number of coins in the machine
        {
            if (money_in_machine_quantity[2]-count>0)
            {
                money_in_machine_quantity[2]-=count;
                break;
            }
        }
        cout<<"5*"<<count<<" ";
        count-=temp1;
        count*=5;
        while(temp>=1) ///count the coins number of the category 1
        {
            temp-=1;
            count++;
        }
        temp1=count;
        for (; count>=0; count--)///confirm the number of coins in the machine
        {
            if (money_in_machine_quantity[1]-count>0)
            {
                money_in_machine_quantity[1]-=count;
                break;
            }
        }
        cout<<"1*"<<count<<" ";
        count-=temp1;
        count*=2;
        while(temp>=0.5) ///count the coins number of the category 0.5
        {
            temp-=0.5;
            count++;
        }
        temp1=count;
        for (; count>=0; count--) ///confirm the number of coins in the machine
        {
            if (money_in_machine_quantity[0]-count>0)
            {
                money_in_machine_quantity[0]-=count;
                break;
            }
        }
        cout<<"0.5*"<<count<<endl;
        count=0;
    }
    void quantity_reduce() ///By subtracting the quantity to the client from the quantity available
    {
        quantity[user_choice]=quantity[user_choice]-user_quantity;
    }
    void new_user() ///processing the machine for the new customer
    {
        user_kind_of_money=0;
        user_money=0;
        user_quant_money=0;
    }
    void machine_stop() ///close the machine when all its products are finished
    {
        int coun=0;
        for (int i=0; i<10; i++)
        {
            if (quantity[i]==0)
                coun++;
        }
        if (coun==10)
            exit(0);
    }
};
istream&operator>>(istream& in,Client&vend)
{
    cout<<"please enter type: ";
    in>>vend.user_type; ///take from The customer product name
    cout<<"please enter the item quantity: ";
    in>>vend.user_quantity; ///take from The customer product quantity
    vend.all_money=0;
    while (true) ///take from The customer the number and type of coins
    {
        cout<<"please enter kind of money money: ";
        in>>vend.user_kind_of_money; /// here take type of coins
        cout<<"please enter the quantity for that kind: ";
        in>>vend.user_quant_money; /// here take the number of coins
        if (vend.user_kind_of_money==20)
            vend.quant_20+=vend.user_quant_money;
        if (vend.user_kind_of_money==10)
            vend.quant_10+=vend.user_quant_money;
        if (vend.user_kind_of_money==5)
            vend.quant_5+=vend.user_quant_money;
        if (vend.user_kind_of_money==1)
            vend.quant_1+=vend.user_quant_money;
        if (vend.user_kind_of_money==0.5)
            vend.quant_05+=vend.user_quant_money;
        vend.all_money+=vend.user_kind_of_money*vend.user_quant_money; ///here we calculate the client's money
        cout<<"if u end press e else press any thing: ";
        string e;
        cin>>e;
        if (e=="e")
            break;
    }
    return in;
}

int main()
{
    In_Vending_Machine fod;
    cout<<"new user"<<endl;
    while (true) ///Works as long as there are products in the machine
    {
        fod.print();///will print the name, number, and price of the product
        fod.new_user(); ///processing the machine for the new customer
        cin>>fod;
        while(true) ///Work as long as the customer wants it
        {
            while (!fod.check_all())///Make sure that the name and number of the product and that the price is equal to or greater than the price of the product
            {
                cout<<"something wrong"<<endl;
                cin>>fod;
            }
            fod.save_money();///save money and numbered
            fod.quantity_reduce();///By subtracting the quantity to the client from the quantity available
            fod.change();///print the change of the money to the customer
            fod.machine_stop(); ///close the machine when all its products are finished
            cout<<"if u want to end enter e: ";
            string end1;
            cin>>end1;
            if (end1 =="e")
                break;
            else
            {
                fod.print();///will print the name, number, and price of the product
                cin>>fod;
            }
        }
        fod.machine_stop();///close the machine when all its products are finished
        cout<<"new user"<<endl;
    }
}
