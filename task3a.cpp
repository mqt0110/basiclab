#include <iostream>
extern "C" {
#include <string.h>
}

using namespace std;

class Photo{

        int code;
        int dpi;
        char *keyword1;
        char *keyword2;
        char *keyword3;
        char *name;
        Photo *next;
 public :
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

             delete  name;
             delete  keyword1;
             delete  keyword2;;
             delete  keyword3;

         }
    friend class Lensman;
}; //dau ket thuc class
class Lensman{
    public:
        Photo *head;
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

    void remove_Photo(int code)
    {
        Photo *current=head;
        Photo *previous= NULL;
        if( head == NULL)
            return;

        while( (current->code)!= code)
            {
                if(!(current->next))
                    return;
                else
                {
                previous=current;  //khai bao 1 con tro du phong de xoa con tro hien tai
                current=current->next;
                }
            }

        if ( current == head)
            {
                head= head->next;  //xoa bo con tro head, thay head moi
            }
        else
            {
                previous->next = current -> next; //bo con tro current
            }
        return; //tra ve danh sach
    }

    int &modify(int dpi, char* keyword1, char* keyword2, char*keyword3, char* name)
{

    Photo *current=head;


    int a,b1,b2,b3,c1,c2,c3,d1,d2,d3,len1,len2;

    //khong xet head, yeu cau tao head truoc
        if(!head)
        {
            cout<<"Cant modify";
        }
        else{
        while(current)// xet con tro current
        {
        //thiet lap gia tri a,b1,b2,b3,c1,c2,c3,d1,d2,d3
        a=strcmp(current->name,name);

        b1=strcmp(current->keyword1,keyword1);
        b2=strcmp(current->keyword1,keyword2);
        b3=strcmp(current->keyword1,keyword3);

        c1=strcmp(current->keyword2,keyword1);
        c2=strcmp(current->keyword2,keyword2);
        c3=strcmp(current->keyword2,keyword3);

        d1=strcmp(current->keyword3,keyword1);
        d2=strcmp(current->keyword3,keyword2);
        d3=strcmp(current->keyword3,keyword3);

        //xet dieu kien

        if (((b1 == 0) || (b2 == 0) || (b3 == 0) ) && ( (c1 == 0) || (c2 == 0) || (c3 == 0) ) &&( (d1 == 0) || (d2 == 0) || (d3 == 0) ) )
        {
            if( a == 0)
            {// cung ten va key , chi co 1 truong hop nen khi phat hien lap tuc break
            current->dpi=dpi;
            return current->dpi;
            break;
            }
            else if (a!=0) // thay ten ,khi cung key nhung khac ten, co the co 2 truong hop
            {
            current->dpi=dpi; // thay dpi
            len1=strlen(name);
            len2=strlen(current->name);

            if(len1 >= len2)
                {
                strncpy(current->name,name,len1);
                current->name[len1]='\0';
                }
            else
                strncpy(current->name,name,len2);


            return current->dpi;
            break;
            }
        } // ngat lenh if
        else
        {

            // kiem tra dieu kien de tao moi neu khong xay ra 2 truong hop tren
           if (current->next)
               {
                   current=current->next; //tiep tuc duyet list
               }
            else //phan tu cuoi list
                {
                    current->next=new Photo((current->code+1),dpi,keyword1,keyword2,keyword3,name);
                   return current->next->dpi;
                    break;
               }

       }// ngat lenh else
        }//ngat lenh while(current)
        }//ngat lenh else





}//dau ket thuc function


    Lensman()
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
    }
};//dau ket thuc Class

int main()
{
    Lensman *p1=new Lensman;
    Lensman p;
    p.add_Photo(100,(char *) "slow",(char *) "animal",(char *) "move",(char *) "Horse riding");  //code :1
    p.add_Photo(300,(char *) "fast",(char *) "animal",(char *) "move",(char *) "Horse riding");  // new Photo  code:2
    p.add_Photo(100,(char *) "slow",(char *) "animal",(char *) "move",(char *) "Horse riding");  //no change
    p.modify(100,(char *) "fast",(char *) "animal",(char *) "move",(char *) "Horse riding");// nothing will change
    p.modify(100,(char *) "slow",(char *) "animal",(char *) "move",(char *) "Horse riding")+=5; //dpi raising print();
    p.modify(100,(char *) "fast",(char *)"anima",(char *) "move",(char *) "Horse ridin"); //creation of a new Photo , code :3
   // p.modify(100,(char *) "slow",(char *) "animal",(char *) "move",(char *) "Horse-ride"); //name substitution
    p.print();
    p.~Lensman();
    p.print();
/*
    p.modify(100,(char *) "slow",(char *) "animal",(char *) "move",(char *) "Horse-ride")=150; // dpi setting
    p.modify(300,(char *) "fast",(char *) "animal",(char *) "move",(char *) "Horse riding"); //dpi modification
    p.print();

    p1->add_Photo(100,(char *) "slow",(char *) "animal",(char *) "move",(char *) "Horse riding");
    p1->add_Photo(100,(char *) "slo",(char *) "animal",(char *) "move",(char *) "Horse riding");
    p1->modify(100,(char *) "slow",(char *) "animal",(char *) "move",(char *) "Horse riding");// nothing will change
    p1->modify(100,(char *) "slow",(char *) "animal",(char *) "move",(char *) "Horse riding")+=5; //dpi raising print();
    p1->modify(100,(char *) "fast",(char *)"animal",(char *) "move",(char *) "Horse riding"); //creation of a new Photo
    p1->modify(100,(char *) "slow",(char *) "animal",(char *) "move",(char *) "Horse-ride"); //name substitution
    p1->print();

    p1->modify(100,(char *) "fast",(char *) "animal",(char *) "move",(char *) "Horse-ride")=150; // dpi setting
    p1->modify(300,(char *) "slow",(char *) "animal",(char *) "move",(char *) "Horse riding"); //dpi modification
    p1->print();
    p1->~Lensman();
    p1->print();*/

    return 0;
}

