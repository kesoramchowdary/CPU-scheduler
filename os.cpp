#include<iostream>

using namespace std;

class os2 {
private:
  int et,tobeplaced,qt1,qt2,noOfProcess,idle;
  bool nan;
  struct process
  {
      int at;//arrival_time
      int bt;//burst time
      int ct;//completed time
      int id;
      int rt;//remaining time
      bool terminated;
  }*p;
public:
  os2 ();
  void get_data();
  void sortat(int size);
  void process_sub(int qt);
  void sortrt();
  void process_data();
  void sortid();
  void put_data();
  ~os2 ();
};

os2::os2(){
  et=0;tobeplaced=0;qt1=6;qt2=10;idle=0;
  get_data();
  process_data();
  put_data();
}

void os2::get_data(){
    cout<<"enter number of processes: ";
    cin>>noOfProcess;
    p = new process[noOfProcess];
    for(int i = 0; i < noOfProcess; i++)
    {
        cout<<"enter arrival time and burst time of p"<<i+1<<": ";
        cin>>p[i].at>>p[i].bt;
        p[i].terminated=true;
        p[i].id=i;
        p[i].rt=p[i].bt;
    }
}

void os2::sortat(int size){
  process temp;
  if(size==-1){
    size=noOfProcess;
  }
  for(int i=0;i<size;i++)
{
  for(int j=0;j<size;j++)
  {
    if(p[i].at<p[j].at){
      temp = p[i];
      p[i]=p[j];
      p[j]=temp;
    }
   }
}
}

void os2::sortrt(){
  process temp;
  for(int i=0;i<noOfProcess;i++)
{
  for(int j=0;j<noOfProcess;j++)
  {
    if(p[i].rt>p[j].rt){
      temp = p[i];
      p[i]=p[j];
      p[j]=temp;
    }
   }
}
}

void os2::sortid(){
  process temp;
  for(int i=0;i<noOfProcess;i++)
{
  for(int j=0;j<noOfProcess;j++)
  {
      if(p[i].id<p[j].id){
      temp = p[i];
      p[i]=p[j];
      p[j]=temp;
    }
   }
}
}

void os2::process_sub(int qt){
  int i =0;
  while (i<noOfProcess) {
    if(p[0].at>et){
      et++;
      continue;
    }
    if(p[i].at<=et){
      //check
      if(p[i].rt==0){
        i++;
        continue;
      }
      if(p[i].rt>=qt){
        et+=qt;
        p[i].ct=et;
        p[i].rt-=qt;
      }
      else{
        et+=p[i].rt;
        p[i].ct=et;
        p[i].rt-=p[i].rt;
      }
      i++;
      continue;
    }
    else{
      if(tobeplaced>=i){
        tobeplaced=0;
      }
      if(p[tobeplaced].rt==0){
        tobeplaced++;
      }
      else{
        if(p[tobeplaced].rt>=qt){
          et+=qt;
          p[tobeplaced].ct=et;
          p[tobeplaced].rt-=qt;
        }
        else{
          et+=p[tobeplaced].rt;
          p[tobeplaced].ct=et;
          p[tobeplaced].rt-=p[tobeplaced].rt;
        }
        tobeplaced++;
      }
    }
  }
}

void os2::process_data(){
  int lcount=0;
  sortat(-1);
  tobeplaced=0;
  process_sub(qt1);
  tobeplaced=0;
  process_sub(qt2);
  sortrt();
    int temprt=p[0].rt;
    for(int i=0;p[0].rt==p[i].rt;i++){
    et+=p[i].rt;p[i].ct=et;
    p[i].rt-=p[i].rt;
    p[i].terminated=false;
  }
}

void os2::put_data(){
  sortid();
  cout<<"processId,arrival_time,burst time,waiting time,turnaround time,terminated\n";
  for(int i = 0; i < noOfProcess; i++)
  {
      cout<<"P"<<i+1<<" | "<<p[i].at<<" | "<<p[i].bt<<" | "//<<p[i].ct<<" | "
      <<(p[i].ct-p[i].at-p[i].bt+p[i].rt)
      <<" | "<<(p[i].ct-p[i].at)<<" | "<<p[i].terminated<<"\n";
  }
}

os2::~os2()
{
}

int main(int argc, char const *argv[]) {
  os2 obj;
  return 0;
}
