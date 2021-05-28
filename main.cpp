/***************************************
 *
 * g++ -o kilo -g main.cpp -lsqlite3 
 * gdb kilo
 * rel 2-08
 * ************************************/


#include <stdio.h>
#include <set>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <strstream>
#include <sqlite3.h>
#include <string.h>
#include <time.h>
#include "escape.h"
#include "int3char.h"
#include "charint.h"

#define DB "/usr/local/share/diet/kkal.db"

std::string datata="data";
const char *cdata=datata.c_str();
char data_end;
int icolor=0;
char gargv[100][100];

static int callback(void *not_used,int argc,char **argv,char **az_col_name)
{
    for (int i=0;i<argc;i++)
    {
        printf("%s= %s\t",az_col_name[i],argv[i]?argv[i]:"NULL");
    }
    printf("\n");
    return 0;
}

static int callback_norma(void *not_used,int argc,char **argv,char **az_col_name)
{
    printf(" arg=%d",argc);
     for (int i=0;i<argc;i++)
    {
        *gargv[i]=*strcpy(gargv[i],argv[i]);
    }
    
    printf("\n");
    return 0;
}

static int callback_dp(void *not_used,int argc,char **argv,char **az_col_name)
{
    using namespace std;
    icolor++;
    if(icolor%2==0)
    {
        set_display_atrib(F_YELLOW);
        set_display_atrib(BRIGH);
    }
    else
    {
        set_display_atrib(F_CYAN);
    }
    for (int i=0;i<argc;i++)
    {
        cout.width(12);
        cout<<az_col_name[i]<<"=";

        if (argv[i]!=NULL){
            CharInt a1(argv[i]);
            CharInt a2(gargv[i]);
            if (a1.integ<a2.integ){
                set_display_atrib(B_RED);
            }
        }
        cout.width(10);
        cout.precision(1);
        cout<<(argv[i]?argv[i]:"NULL");
        set_display_atrib(B_DEFAULT);
        if ((i+1)%4==0){cout<<"\n";}
    }
    resetcolor();
    cout<<"\n\n";
    return 0;
}

static int callback_food(void *not_used,int argc,char **argv,char **az_col_name)
{
    using namespace std;
    icolor++;
    if(icolor%2==0)
    {
        //set_display_atrib(F_BLUE);
        //set_display_atrib(BOLD);
    }
    else
    {
        set_display_atrib(F_CYAN);
        set_display_atrib(BOLD);
    }
    for (int i=0;i<argc;i++)
    {
        if (strcmp(az_col_name[i],"name")==0){
            cout<<"\n";//<<az_col_name[i];
            set_display_atrib(B_YELLOW);
            cout<<(argv[i]);
            set_display_atrib(B_DEFAULT);
            cout<<"\n";
        }
    }
    for (int i=0;i<argc;i++)
    {
        cout.width(10);
        if (strcmp(az_col_name[i],"name")!=0){
          cout<<az_col_name[i]<<"= ";
          cout.width(7);
          cout.precision(1);
          cout<<(argv[i]?argv[i]:"NULL")<<"  ";
        }
        if ((i+1)%4==0){cout<<"\n";}
    }
    resetcolor();
    cout<<"\n";
    return 0;
}

static int callback_pot(void *not_used,int argc,char **argv,char **az_col_name)
{
    using namespace std;
    icolor++;
    if(icolor%2==0)
    {
        set_display_atrib(F_YELLOW);
        set_display_atrib(BOLD);
    }
    else
    {
        set_display_atrib(F_CYAN);
    }
    for (int i=0;i<argc;i++)
    {
        if(strcmp(az_col_name[i],cdata)==0)
        {
            const size_t lande=sizeof argv[i];
            if (data_end==argv[i][lande+1])
            {
                //cout<< argv[i]<<" ### "<<data_end<< " ^^^ "<<lande;
            }
            else
            {
                data_end=argv[i][lande+1];
                cout<<"\n"<<argv[i]<<"\n";
            }
        }
        cout.width(5);
        cout<<az_col_name[i]<<"= ";
        cout.width(4);
        cout.precision(1);
        cout<<(argv[i]?argv[i]:"NULL")<<"  ";
    }
    cout<<"\n";
    resetcolor();
    return 0;
}

int error(int rc,char *msg,char *z_err_mes,char* ok)
{
    if(rc)
    {
        fprintf(stderr,msg, z_err_mes);
        sqlite3_free(z_err_mes);
    }
    else {fprintf(stdout,ok);}
    return 0;
}

int select_max_food(sqlite3 *db){

    std::cout<<"\nОтбор максимального содержания элемента в продуктах"
        "\nэлемент(н.:vitb2) количество? ";
    char elem[20],cou[20];
    char *z_err_mes=0;
    
    std::cin>>std::setw(20)>>elem>>std::setw(20)>>cou;
    std::string ssql="select * from food_ordnung order by "
        +(std::string)elem+" desc limit "+(std::string)cou+" ;";
    std::cout<<ssql;
    const char *sql=ssql.c_str();
    int rc=sqlite3_exec(db,sql,callback_food,0,&z_err_mes);
    error(rc,"not select %s\n",z_err_mes,"select ok\n");
}

int select(sqlite3 *db,char *table)
{
    char *z_err_mes=0;
    char *sql;
    if(table=="norma")
    {
        sql="select * from dp where data like 'norma';";
        int rc=sqlite3_exec(db,sql,callback_norma,0,&z_err_mes);
        error(rc,"not select %s\n",z_err_mes,"select ok\n");
    }
    if(table=="dp")
    {
        sql="select * from dp;";
        int rc=sqlite3_exec(db,sql,callback_dp,0,&z_err_mes);
        error(rc,"not select %s\n",z_err_mes,"select ok\n");
    }
    if(table=="food")
        {
            sql="select kkal,foodid,name from food order by name;";
            int rc=sqlite3_exec(db,sql,callback_food,0,&z_err_mes);
            error(rc,"not select %s\n",z_err_mes,"select ok\n");
        }
    if(table=="food_all")
        {
            std::cout<<"Название продукта? ";
            char nameprod[100];
            std::cin>>nameprod;
            std::cout<<nameprod;
            std::string ssql="select * from food_ordnung where name like '%"+ (std::string)nameprod+"%' order by name ;";
            std::cout<<ssql;
            const char *sql=ssql.c_str();
            int rc=sqlite3_exec(db,sql,callback_food,0,&z_err_mes);
            error(rc,"not select %s\n",z_err_mes,"select ok\n");
        }
    if(table== "pot")
        {
            sql="select data,potid,pot.foodid,massa100g,name from pot"
                " left join food on pot.foodid=food.foodid;";
            int rc=sqlite3_exec(db,sql,callback_pot,0,&z_err_mes);
            error(rc,"not select %s\n",z_err_mes,"select ok\n");
        }

    return 0;

}
int insert(sqlite3 *db,char *table,char *sysdat,char *id,char *massa)
{
    char *z_err_mes=0;
    if (table=="pot")
    {
        std::string ssql="insert into pot(foodid,massa100g,data) values('"+\
          (std::string)id+"','"+massa+"','"+sysdat+"');";
        const char *sql=ssql.c_str();
        int rc=sqlite3_exec(db,sql,callback,0,&z_err_mes);
        error(rc,"not insert %s\n",z_err_mes,"добавлено's\n");
    }
    return 0;
}
int insert_food(sqlite3 *db)
{
    using namespace std;
    char *z_err_mes=0;
    const int ni=55; //длина массива 
    cout<<"\nНовый продукт (ввод данных в микрограммах):\n"
        "\tname (завершение ввода знак =) ";
    char namee[300];
    cin.getline(namee,300,'=');
    //удаление начального \n
    char name[300];
    for (int i=0;i<300;i++){
        if (i!=0){
            name[i-1]=namee[i];
            }

        }
    char kkal[ni],belokrast[ni],belokgivot[ni],girnas[ni],girmono[ni],girpoli[ni];
    cout<<"\nkkal belokrast belokgivot girnas girmono girpoli\n";
    cin>>setw(ni)>>kkal>>setw(ni)>>belokrast>>setw(ni)>>belokgivot>>setw(ni)>>girnas>>setw(ni)>>girmono>>setw(ni)>>girpoli;
    char uglevod[ni], klet[ni],kofein[ni],alcohol[ni], vita[ni],vitb1[ni];
    cout<<"\nuglevod klet kofein accohol vita vitb1\n";
    cin>>setw(ni)>>uglevod>>setw(ni)>>klet>>setw(ni)>>kofein>>setw(ni)>>alcohol>>setw(ni)>>vita>>setw(ni)>>vitb1;
    char vitb2[ni], vitb4[ni], vitb5[ni], vitb6[ni], vitb9[ni], vitb12[ni];
    cout<<"\n vitb2  vitb4  vitb5  vitb6  vitb9  vitb12\n";
    cin>>setw(ni)>> vitb2>>setw(ni)>>vitb4>>setw(ni)>>vitb5>>setw(ni)>>vitb6>>setw(ni)>>vitb9>>setw(ni)>>vitb12;
    char vitc[ni], vitd[ni], vite[ni], vith[ni], vitk[ni], vitrr[ni];
    cout<<"\n vitc vitd vite vith vitk vitrr\n";
    cin>>setw(ni)>> vitc>>setw(ni)>>vitd>>setw(ni)>>vite>>setw(ni)>>vith>>setw(ni)>>vitk>>setw(ni)>>vitrr;
    char bcar[ni], b[ni], br[ni], ca[ni], cl[ni], co[ni];
    cout<<"\n bcar b br ca cl co\n";
    cin>>setw(ni)>> bcar>>setw(ni)>> b>>setw(ni)>> br>>setw(ni)>> ca>>setw(ni)>> cl>>setw(ni)>> co;
    char chrom[ni],cu[ni],ftor[ni],fe[ni],i[ni],k[ni];
    cout<<"\n chrom cu ftor fe i k\n";
    cin>>setw(ni)>> chrom>>setw(ni)>>cu>>setw(ni)>>ftor>>setw(ni)>>fe>>setw(ni)>>i>>setw(ni)>>k;
    char mg[ni],mn[ni],mo[ni],na[ni],p[ni],s[ni];
    cout<< "\nmg mn mo na p s\n";
    cin>>setw(ni)>> mg>>setw(ni)>>mn>>setw(ni)>>mo>>setw(ni)>>na>>setw(ni)>>p>>setw(ni)>>s;
    char selen[ni],si[ni],zn[ni];
    cout<<"\n selen si zn\n";
    cin>>setw(ni)>> selen>>setw(ni)>>si>>setw(ni)>>zn;

    string sql2="insert into food("
        "name,kkal,belokrast,belokgivot,girnas,girmono,girpoli,uglevod,"
         "klet,kofein,alcohol,vita,vitb1,vitb2, vitb4, vitb5, vitb6, vitb9,"
         "vitb12, vitc, vitd, vite, vith, vitk, vitrr, bcar, b, br, ca, cl, co,"
        "chrom,cu,ftor,fe,i,k, mg,mn,mo,na,p,s, selen,si,zn"
        ") values('"+(string)name+"',"+(string)kkal+","+(string)belokrast+","
        +(string)belokgivot+","+(string)girnas+","+(string)girmono+","
        +(string)girpoli+","+(string)uglevod+","+(string)klet+","+(string)kofein
        +","+(string)alcohol+","+(string)vita+","+(string)vitb1+","+(string)vitb2
        +","+(string)vitb4+","+(string)vitb5+","+(string)vitb6+","+(string)vitb9
        +","+(string)vitb12+","+(string)vitc+","+(string)vitd+","+(string)vite
        +","+(string)vith+","+(string)vitk+","+(string)vitrr+","+(string)bcar
        +","+(string)b+","+(string)br+","+(string)ca+","+(string)cl+","+(string)co
        +","+(string)chrom+","+(string)cu+","+(string)ftor+","+(string)fe
        +","+(string)i+","+(string)k+","+(string)mg+","+(string)mn+","+(string)mo
        +","+(string)na+","+(string)p+","+(string)s+","+(string)selen
        +","+(string)si+","+(string)zn+");";
        cout<<"\n"<<sql2<<"\n"
        <<" ? (1/0)(y/n)";
        char yes;
        cin>>yes;
        if (yes=='Y'||yes=='y'||yes=='1')
        {
            const char *sql=sql2.c_str();
            int rc=sqlite3_exec(db,sql,callback,0,&z_err_mes);
            error(rc,"not insert %s\n",z_err_mes,"добавлено's\n");
        }
        else { std::cout<<"\nотмена\n"; }
     return 0;
}

int update_pot_data(sqlite3 *db,char *potid,char *sysdat)
{
    char *z_err_mes=0;
    std::string ssql="update pot set data='"+(std::string)sysdat+\
        "' where potid="+(std::string)potid+";";
    const char *sql=ssql.c_str();
    int rc=sqlite3_exec(db,sql,callback,0,&z_err_mes);
    error(rc,"not update %s\n",z_err_mes,"\nзамена проведена\n");
    return 0;
}

int update_pot_foodid(sqlite3 *db,char *potid,char *id)
{
    char *z_err_mes=0;
    std::string ssql="update pot set foodid='"+(std::string)id+\
        "' where potid="+(std::string)potid+";";
    const char *sql=ssql.c_str();
    int rc=sqlite3_exec(db,sql,callback,0,&z_err_mes);
    error(rc,"not update %s\n",z_err_mes,"\nзамена проведена\n");
    return 0;
}

int update_pot_massa(sqlite3 *db,char *potid,char *massa)
{
    char *z_err_mes=0;
    std::string ssql="update pot set massa100g='"+(std::string)massa+\
        "' where potid="+(std::string)potid+";";
    const char *sql=ssql.c_str();
    int rc=sqlite3_exec(db,sql,callback,0,&z_err_mes);
    error(rc,"not update %s\n",z_err_mes,"\nзамена проведена\n");
    return 0;
}

int update_food(sqlite3 *db,char *foodid,char *parms, char *vals)
{
    char *z_err_mes=0;
    std::string ssql="update food set "+(std::string)parms
        +"='"+(std::string)vals
        +"' where foodid="+(std::string)foodid+";";
    const char *sql=ssql.c_str();
    int rc=sqlite3_exec(db,sql,callback,0,&z_err_mes);
    error(rc,"not update %s\n",z_err_mes,"\nзамена проведена\n");
    return 0;
}

int get_nowdate(std::string &strdata)
{
    time_t t= time(NULL);
    struct tm* dnow = localtime(&t);
    const int nYear = dnow->tm_year+1900;
    const int nMon = dnow->tm_mon+1;
    const int nDay = dnow->tm_mday;

    IntChar icYear(nYear);
    IntChar icMon(nMon);
    IntChar icDay(nDay);
    const std::string cYear = icYear.text;
    const std::string cMonat  = icMon.text;
    const std::string cDayl  = icDay.text;
    const std::string cMon = (cMonat.size()==1 ? "0"+cMonat : cMonat);
    const std::string cDay = (cDayl.size()==1 ? "0"+cDayl:cDayl);
    const std::string cData = cYear+"-"+cMon+"-"+cDay;
    strdata=cData;
    return 0;
}
int main(int argc,char **argv)
{
    setlocale(LC_ALL,"Russian");
    sqlite3 *db;
    char *z_err_mes=0;
    int rc=sqlite3_open(DB,&db);
    if (rc) 
    {
        fprintf(stderr,"не могу открыть %s\n",sqlite3_errmsg(db));
        return 1;
    }
    else
    {
        fprintf(stdout,"открыл rc= %d \n",rc);
    }

    char sel='a';
    char foodid[10];
    char potid[10];
    char parms[15];
    char vals[15];
    char massa[15];
    char yes='Д';
    const char *menu="\n Выбор действия :"
        "\n\td - установка даты,\t\tf - редактирование продуктов,"
        "\n\t1 - просмотр рациона, \t\t2 - просмотр результата,"
        "\n\t3 - добавление рациона,\t\t4 - замена даты рациона на текущую,"
        "\n\t5 - ред. количества рациона,\t6 - редактирование продукта рациона,"
        "\n\t7 - просмотр продуктов,\t\t\8 - добавление продуктов,"
        "\n\t9 - просмотр макс. элементов,\t0 - выход ? ";
    std::string strdata="2020-03-17";
    get_nowdate(strdata);
    const char *nsysdat=strdata.c_str();
    const size_t sizze=256;
    char sysdat[sizze]="2020-03-17";
    char tsysdat[256]="2020-03-17";
    strcpy(sysdat,nsysdat);
    std::cout<<"\n Текущая дата = "<<sysdat;
    while (sel!='0')
    {
        switch (sel)
        {
            case 'd':
                printf("\nСтарая дата = %s\tНовая дата = ",sysdat);
                std::cin >> tsysdat;
                std::cout<<"Ввод новой даты : "
                    <<"\e["<<F_GREEN<<"m"<< tsysdat
                    <<"\e[0m"<<" ? (1/0)(y/n)";
                std::cin>>yes;
                if (yes=='Y'||yes=='y'||yes=='1')
                {
                    strcpy(sysdat,tsysdat);
                }
                else { std::cout<<"\nотмена\n"; }
                printf("\n дата = %s\n ",sysdat);
                break;
            case '1':
                select(db,"pot");
                break;
            case '2':
                select(db,"norma");
                select(db,"dp");
                break;
            case '3':
                select(db,"food");
                printf("\n Ввод : foodid масса(100 грамм) ? ");
                std::cin>>foodid>>massa;
                printf("\n Ввод : foodid=%s масса(100 грамм)=%s ? (1/0)(y/n)",foodid,massa);
                std::cin>>yes;
                if (yes=='Y'||yes=='y'||yes=='1')
                {
                    //std::cout<<yes;
                    insert(db,"pot",sysdat,foodid,massa);
                }
                else { std::cout<<"\nотмена\n"; }
                break;
            case '4':
                select(db,"pot");
                printf("\n Замена : potid ? ");
                std::cin>>potid;
                printf("\n Замена : potid = %s дата = %s ? (1/0)(y/n)",potid,sysdat);
                std::cin>>yes;
                if (yes=='Y'||yes=='y'||yes=='1')
                {
                    update_pot_data(db,potid,sysdat);
                }
                else { std::cout<<"\nотмена\n"; }
                break;
            case '5':
                select(db,"pot");
                printf("\n Замена : potid massa ? ");
                std::cin>>potid>>massa;
                printf("\n Замена : potid = %s massa = %s ? (1/0)(y/n)",potid,massa);
                std::cin>>yes;
                if (yes=='Y'||yes=='y'||yes=='1')
                {
                    //std::cout<<yes;
                    update_pot_massa(db,potid,massa);
                }
                else { std::cout<<"\nотмена\n"; }
                break;
            case '6':
                select(db,"pot");
                printf("\n Замена : potid foodid? ");
                std::cin>>potid>>foodid;
                printf("\n Замена : potid = %s foodid = %s ? (1/0)(y/n)",potid,foodid);
                std::cin>>yes;
                if (yes=='Y'||yes=='y'||yes=='1')
                {
                    //std::cout<<yes;
                    update_pot_foodid(db,potid,foodid);
                }
                else { std::cout<<"\nотмена\n"; }
                break;
            case '7':
                select(db,"food_all");
                break;
            case '8':
                insert_food(db);
                break;
            case '9':
                select_max_food(db);
                break;
            case 'f':
                select(db,"food_all");
                printf("\n Замена : foodid свойство(н.:ftor) значение(н.:1500)? ");
                std::cin>>foodid>> parms>> vals;
                printf("\n Замена : foodid = %s %s = %s? (1/0)(y/n)",foodid,parms,vals);
                std::cin>>yes;
                if (yes=='Y'||yes=='y'||yes=='1')
                {
                    //std::cout<<yes;
                    update_food(db,foodid,parms,vals);
                }
                else { std::cout<<"\nотмена\n"; }
                break;

        }
        printf(menu);
        std::cin>>sel;
    }

    sqlite3_close(db);
    return 0;
}


/*    char sql[]="create table com ("\
               "id integer primary key autoincrement,"\
               "name text not null);";
    rc=sqlite3_exec(db,sql,callback,0,&z_err_mes);
    error(rc,"sql err %s\n", z_err_mes,"all ok\n");
    */
