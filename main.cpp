//使用链表存储相应所有正在计算的task，按用户分队列计算，每0.1s进行一次检查操作，如果发现任务已完成，则调用下一任务，如如发现任务如果发现请求资源不够，则调用扩展资源函数，如果发现当前资源利用率小于50%,调用资源减少函数

#include <iostream>
#include </usr/include/mysql/mysql.h>
//#include <sql/mysql.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <list>

using namespace std;
int totalcores;
int cores_available;
class calc_task;
list<calc_task> task_list;
int user_list[2048];//to simplify, as a demo, we think that our user amount won't be more than 2048 
int user_numb;
std::list<calc_task>::iterator it1;

#define MTASK_WAITTING  0
#define MTASK_RUNNING   1
#define MTASK_KILLED    3
#define MTASK_ABORTED  -1
#define MTASK_FINISHED  2
#define MTASK_AHEADED   5
#define MTASK_HANGUP    6

#define MPROG_RUN       1
#define MPROG_KILL      2
#define MPROG_PACK      3    
#define MPROG_FINISH    4

#define enlarge() cores_available=totalcores;//improve later
#define reduce();//cores_availabe=( (cores_available/2) > totalcores)? cores_available/2 :totalcores;


class calc_task{

    pid_t pid;
    int start_time;
    int finish_time;
    FILE *nutdf;
public:
    int status;//构造时设为MTASK_WAITTING
    int serial;
    int task_mark;
    //int predict_time;
    int cores;
    int time;
    int type;
    char name[1024];
    int user;
    
#define paraset(a) user_list[this->user] a 1;totalcores a this->cores;
    int change_task_status(int i)
    {
        //this requires sql;!!!!
    }
    int getcmd(int type,char *cmd)
    {
        //this program will run another programs(not the qe itself),the program will detect if the qe normally exited or not.
        //char ...;//system settings...
        switch(type)
        {
            case MPROG_RUN:     ;break;
            case MPROG_KILL:    ;break;
            case MPROG_PACK:    ;break;
            case MPROG_FINISH:  ;break;
        }
    }
    int start()
    {
        char cmd[1024];
        nutdf=popen("/usr/bin/nut","w");
        //submit message to the nut deamon.
        fprintf(nutdf,"%ld%ld%ld%ld\n",this->serial,this->cores,this->type);
        fflush(nutdf);
        //
       // this->start_time=time(0);
        paraset(+=);
        if(cores_available<totalcores)
        {
            enlarge();
        }
        this->change_task_status(MTASK_RUNNING);
    //attention:finish function is runing in the main program! 
    }
    int kill()
    {
        char cmd[1024];
        //submit
        fprintf(nutdf,"c\n");
        fflush(nutdf);
        //
        paraset(-=);
        this->change_task_status(MTASK_KILLED);
        this->clean();
    }
    int unexpectabort()
    {
        paraset(-=);
        this->change_task_status(MTASK_ABORTED);
    }
    int finish()
    {
        this->clean();
        this->pack();
        
        this->time=this->finish_time-this->start_time;
        this->change_task_status(MTASK_FINISHED);
    }
    int pack()
    {
        //nutdeamon will finish the first step of package
        char cmd[1024];
        this->getcmd(MPROG_PACK,cmd);
        //popen("");//unfinished
    }
    int clean()
    {
        ;//this function will be written later.
    }
};

//this requires sql;
//check_finished should be earlier running than this function.
//check the current user mount, and how many users requires the calculating now.
//build a chain list for each "live" user's current task and insert the current possible task for each user,then running it.
//attention! there may will be a delay between the database server and the calculating server.
//if resources are limited, expand,or, if current resources available is 50% percent more than the resources used, call reduce function.
int get_current_task(MYSQL *mysqldb)
{
    int i;
    char sql_cmd[2048];
    list<calc_task> task_require;
    calc_task ttask;
    MYSQL_RES *sql_result;
    MYSQL_ROW *sql_result_row;
    MYSQL_FIELD *sql_result_field;
    //std::list<calc_task>::iterator it2;
    //...
    //first, any user should have at least one task running immediately after submit,
    //and it should follow the submit order.
    //second, if their is any extra cores, first, we should finish the works. if their is no extra work(all work finished, be careful), call the reduce function.
    //首先，轮询当前任务已完成的用户（user_list[i]=0）
        ///add into task_require;
        for(i=1;i<user_numb;i++)
        {
            if(user_list[i])
                continue;
            sprintf(sql_cmd,"SELECT TOP 0 * FROM task_list where user=%ld\
 and cancel_state=0 and (running_state=%ld or running_state=%ld)",i,MTASK_WAITTING,MTASK_HANGUP);
            mysql_query(mysqldb,sql_cmd);
            sql_result=mysql_store_result(mysqldb);
            sql_result_row=mysql_fetch_row(sql_result);
<<<<<<< HEAD
            ///...
=======
            sscanf(sql_result_row[1],"%ld%ld%ld%ld",&(ttask.serial),&(ttask.user),&ttask.cores);//this has some problem
            ttask.start();
            task_list.push_back(task);
            mysql_free_result(sql_result);
>>>>>>> b57aa79769ca4722767e3d070689c19264f2735d
        }
        //有机会的话重构这一段
        //for(it1=task_require.begin();it1!=task_require.end();it1++)
       // {
        //    it1->start();
       //     task_list.push_back(*it1);
       // }
       // task_require.clear();
        //--
    if(totalcores<cores_available)
    {
<<<<<<< HEAD
        while(totalcores<cores_available)
        {
                //int task_added=0;
                sprintf(sql_cmd,"SELECT * FROM task_list where\
 and cancel_state=0 and (running_state=%ld or running_state=%ld)\
 and cores<%ld",i,MTASK_WAITTING,MTASK_HANGUP,cores_available-totalcores);
                mysql_query(mysqldb,sql_cmd);
                sql_result=mysql_store_result(mysqldb);
                sql_result_row=mysql_fetch_row(sql_result);
                //如有空余资源，首先轮询所有可能任务并加入
                //有机会的话重构这一段
                for(it1=task_require.begin();it1!=task_require.end();it1++)
                {
                    it1->start();
                    task_list.push_back(*it1);
                    task_added++;
                }
                task_require.clear();
                //--
        }
=======
            while(totalcores<cores_available)
            {
                sprintf(sql_cmd,"SELECT TOP 10 * FROM task_list where user=%ld and cancel_state=0 and running_state=%ld",i,MTASK_WAITTING);
                mysql_query(mysqldb,sql_cmd);
                sql_result=mysql_store_result(mysqldb);
                int i;
                while(sql_result_row=mysql_fetch_row(sql_result)&&totalcores<cores_available)
                {
                    sscanf(sql_result_ro2w[1],"%ld%ld%ld%ld",&(ttask.serial),&(ttask.user),&ttask.cores);//this has some problem;
                    ttask.start();
                    task_list.push_back(task);
                }
                mysql_free_result(sql_result);
        //如有空余资源，首先轮询所有可能任务并加入
            //有机会的话重构这一段
            }
            //--
>>>>>>> b57aa79769ca4722767e3d070689c19264f2735d
        //如发现无任务可加入，检查是否需要缩减资源开销
        if(cores_available/2>totalcores)
        {
            reduce();
            break;
        }
    }
    
}

//check if there is a finished/aborted/wait_to_be_killed(!this is different with MTASK_KILLED state) program.(the aborted program will have a "failed" file)
//finish all the things should do, after that, the get_current_task() will wipe out the task variables.
int check_if_finished(MYSQL &mysqldb)
{
   
    //task_list *tp,*tpp;
   char s[2048],cmd[2048];
    FILE *t;
    int i,finish_type,leaf=0;
    //std::list<calc_task>::iterator it2;   
    
    for(it1=task_list.begin();it1!=task_list.end();it1++)
   // tpp=&task_list_header;//header(the first guy in the list) will not storage the real task. because it sould not be changed.
   // while(tp=enum_task(tpp))
    {
        sprintf(s,"//tmp//nutd//%ld.finish",it1->serial);
        if(t=fopen(s,"r"))
            
        {
            leaf=1;
            //it means that the nut has already finished
            fscanf(t,"%d",&finish_type);
            fclose(t);
            switch(finish_type)
            {
                case MTASK_ABORTED:it1->unexpectabort();break;
                case MTASK_FINISHED:it1->finish();break;
            }
            it1->finish();
            task_list.erase(it1);
        }
      //  else tpp=tp;
    }
    
    //停止所有waitting_to_be_cancelled 任务。首先检测任务是否已经开始，是否已经结束，然后...
    //wait_to_be_cancelled 与运行状态属于两个字段，不阻塞
    //
    //查出所有已经运行了的需要取消的任务
     sprintf(sql_cmd,"SELECT * FROM task_list where\
 and cancel_state=1 and running_state=%ld or running_state=%ld)"
 ,i,MTASK_WAITTING,MTASK_HANGUP);
    mysql_query(mysqldb,sql_cmd);
    sql_result=mysql_store_result(mysqldb);
    sql_result_row=mysql_fetch_row(sql_result);
    ///...
    
    //查出所有未运行需要取消的任务
    sprintf(sql_cmd,"SELECT * FROM task_list where\
 and cancel_state=1 and running_state=%ld or running_state=%ld)"
 ,i,MTASK_WAITTING,MTASK_HANGUP);
    mysql_query(mysqldb,sql_cmd);
    sql_result=mysql_store_result(mysqldb);
    sql_result_row=mysql_fetch_row(sql_result);
    //...
    
    return leaf;
}

int main(int argc, char **argv)
{
    int i;
    
    const char *host = "localhost";
    const char *user = "root";
    const char *pass = "123456";
    const char *db   = "test";
    
    MYSQL mysqldb;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
    MYSQL_FIELD *fd;
    
    mysql_init(&mysqldb);
    
    if (!mysql_real_connect(&mysqldb, host, user, pass, db, 0, NULL, 0))
    {
        printf("%s", mysql_error(&mysqldb));
    }
    while(1)
    {
        sleep(1000);
        if(check_if_finished(&mysqldb))
            get_current_task(&mysqldb);
    }
   // printf("HelloWorld!");
    return 0;
}

