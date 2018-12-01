#include <iostream>
extern "C" {
#include <string.h>
}

using namespace std;

class Photo{
  public :
        int code;
        int dpi;
        char *keyword1;
        char *keyword2;
        char *keyword3;
        char *name;
        Photo *next;

         Photo(int code,int dpi,char *keyword1,char *keyword2,char *keyword3,char *name) : code(code), dpi(dpi)
         {
             int len=strlen(name);
             this->name= new char [len+1];
             strcpy(this->name, name);

            len=strlen(keyword1);
            this->keyword1= new char [len+1];
            strcpy(this->keyword1, keyword1);

            len=strlen(keyword2);
            this->keyword2= new char [len+1];
            strcpy(this->keyword2, keyword2);

            len=strlen(keyword3);
            this->keyword3= new char [len+1];
            strcpy(this->keyword3, keyword3);

            this->next = NULL;
         }

         ~Photo()
         {

             delete name;
             delete keyword1;
             delete keyword2;;
             delete keyword3;

         }

};
class Lensman{
    public:
        Photo *head=NULL;
    int add_Photo(int dpi, char *keyword1, char *keyword2, char *keyword3, char *name)
    {
        Photo *current = head;
        Photo *tmp= NULL;
        Photo *previous=head;


        int a,b,c,d,e,b1,b2,b3,c1,c2,c3,d1,d2,d3,len;
        int mark=0;
        int maxcode=0;
        int delcode;
        // lenh check phan dau, neu trong thi them anh moi
        if(!head)  // neu head trong, chi them anh
            {
            head= new Photo(1,dpi,keyword1,keyword2,keyword3,name);
            maxcode++;
            return 0;
            }
        else{ //head khong trong, so sanh
        //head  khong trong thi bat dau check
        while (current) //kiem tra con tro hien tai
        {


            //CHECK NAME VA KEYWORD
            a=strcmp(current->name, name);

            b1=strcmp(current->keyword1,keyword1);
            b2=strcmp(current->keyword1,keyword2);
            b3=strcmp(current->keyword1,keyword3);

            c1=strcmp(current->keyword2,keyword1);
            c2=strcmp(current->keyword2,keyword2);
            c3=strcmp(current->keyword2,keyword3);

            d1=strcmp(current->keyword3,keyword1);
            d2=strcmp(current->keyword3,keyword2);
            d3=strcmp(current->keyword3,keyword3);

            e=current->dpi - dpi;

        if((b1 == 0) || (b2 == 0) || (b3 == 0))
            b=0;
        else
            b=-1;


        if((c1 == 0) || (c2 == 0) || (c3 == 0))
            c=0;
        else
            c=-1;


        if((d1 == 0) || (d2 == 0) || (d3 == 0))
            d=0;
        else
            d=-1;

            //check dieu kien
            //1: cung ten va key
            if( (a == 0) && ( b==0)&& (c==0) && (d==0) )
                {
                    if(e>=0) //dpi cu lon hon dpi moi
                        {
                            mark=-1;
                            return -1;
                            break;// bo qua va ngung  duyet list  --- viec xe t nay chi co 1 , neu trung vs 1 phan tu thi co the break, bo qua vong lap while(current)  /// khong thoat vong lap do can di den cuoi list, chi xoa con tro hien tai
                        }
                    else // thay dpi, code va doi vi tri --- cũng chi co 1 phan tu va co the break sau khi xong viec
                    { //co 3 truong hop, 1: head , 2: mot vi tri bat ky trong lít, 3: cuoi list
                        mark=-2;
                        delcode=current->code;
                         // ghi du lieu cho con tro tam int len=strlen(name);

                        tmp=new Photo(current->code, dpi, current->keyword1,current->keyword2,current->keyword3,current->name);  // ghi du lieu cho con tro tam
                    // xoa con tro current
                        if(current == head)
                            head=head->next;
                        else
                        {
                            previous->next=current->next;
                        }
                        current=current->next; //tiep tuc duyet list, khong break do can tao file o cuoi

                    }
                }

            //2: khac ten
           else
               {

              if(current->next)
                  {
                        previous=current;
                        current=current->next;  //tiep tuc duyet list

                  }
                else
               {  //cuoi list
                    if(mark == 0)
                        {
                            current->next=new Photo(current->code+1, dpi, keyword1,keyword2,keyword3,name);
                        return 0;
                        }
                    else if(mark == -2)
                        {

                        current->next=tmp;
                        current->next->code = current->code+1;

                        return 0;
                        }
               }
              }
            } // dau ket thuc lenh while


        }//ket thuc lenh else


}//dau ket thuc function

    void print()
    {
        Photo *current=head;
            cout<<"Photo list :" << endl;
            while (current)
            {
                cout<<"Code: " << current->code<<endl;
                cout<<"Name: " << current->name<<endl;
                cout<<"Dpi:  " << current->dpi<<endl;
                cout<<"Keyword 1 : "<<current->keyword1<<endl;
                cout<<"Keyword 2 : "<<current->keyword2<<endl;
                cout<<"Keyword 3 : "<<current->keyword3<<endl;
                cout<<endl;

            current=current->next;
            }
            cout<<endl;
            cout<<endl;
            cout<<"End of list"<<endl;
            cout<<endl;
    }



 /*   Lensman()
    {
        head=NULL;
    }

    ~Lensman()
    {
        Photo *current=head;
        while(current)
        {
            current=current->next;
            delete head;
            head=current;
        }
    } */

};//dau ket thuc Class

int main()
{
    Lensman *p=new Lensman;
    Lensman p1;
    p1.add_Photo(100,(char*) "A", (char*) "B" , (char*) "C" , (char*) "FS");//code:1
    p1.add_Photo(100,(char*) "A", (char*) "B" , (char*) "C" , (char*) "D"); //code :2
    p1.add_Photo(300,(char*) "A", (char*) "D" , (char*) "C" , (char*) "E");  //tao moi code: 3
    p1.add_Photo(50,(char*) "C", (char*) "B" , (char*) "A" , (char*) "D");  //khong thay doi, trung so 2
    p1.add_Photo(200,(char*) "B", (char*) "C" , (char*) "A" , (char*) "D");   // thay code va dpi   -- tu dong triet tieu , kiem tra dieu kien 2  , code:4
    p1.add_Photo(2000,(char*) "B", (char*) "C" , (char*) "A" , (char*) "C");

    p1.print();
/*
    p->add_Photo(100,(char*) "A", (char*) "B" , (char*) "C" , (char*) "FS");//code:1
    p->add_Photo(100,(char*) "A", (char*) "B" , (char*) "C" , (char*) "D"); //code :2
    p->add_Photo(300,(char*) "A", (char*) "D" , (char*) "C" , (char*) "E");  //tao moi code: 3
    p->add_Photo(50,(char*) "C", (char*) "B" , (char*) "A" , (char*) "D");  //khong thay doi, trung so 2
    p->add_Photo(200,(char*) "B", (char*) "C" , (char*) "A" , (char*) "D");   // thay code va dpi   -- tu dong triet tieu , kiem tra dieu kien 2  , code:4

   p->print();
*/
    return 0;
}

