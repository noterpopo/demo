#include<iostream>
#include<vector>
#include<stack>
#include<ctime>
using namespace std;

int K=4;
int M=8;
int N=4;
int maxp=0;
int tik=0;
void display(int **arr);
int  find(int **arr,int posx,int posy,int point);
vector<int> reset(int **arr);
int calculatePoints(int leftNum,int downNum,int rightNum,int upNum);
void K1(int **arr);
int **clone(int **oarr);
//void KN(int **arr,int n,int ip);
void KN();
void KN_y();
class StepMap
{
public:
    int point;
    int **map;
    int num;
    StepMap(int p,int **m,int n)
    {
        point=p;
        map=m;
        num=n;
    }

};
stack<StepMap> stackmap;
int main(int argc, char const *argv[])
{
    int number=0;
    cin>>number;
    int **arr=new int*[M];
    for(int i=0;i<M;++i)
    {
        arr[i]=new int[N];
    }
    for(int i=0;i<M;++i)
    {
        for(int j=0;j<N;++j)
        {
//            int n=rand()%K+1;
//            arr[i][j]=n;
                cin>>arr[i][j];
        }
    }
    int **tarr=clone(arr);
    maxp=0;
    stackmap.push(StepMap(0,arr,number));
    clock_t start_time = clock();
    KN();
    cout<<"time: "<<clock()-start_time<<endl;
    cout<<tik<<endl;

    cout<<" @@@"<<maxp<<endl;

    stackmap.push(StepMap(0,tarr,number));
    start_time = clock();
    maxp=0;
    KN_y();
    cout<<"time: "<<clock()-start_time<<endl;
    cout<<tik<<endl;

    cout<<" ***"<<maxp<<endl;


    return 0;
}

void display(int **arr)
{
    for(int i=0;i<M;++i)
    {
        for(int j=0;j<N;++j)
        {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
vector<int> reset(int **arr)
{
    vector<int> temp;
    for(int i=0;i<M;++i)
    {
        for(int j=0;j<N;++j)
        {
            if(arr[i][j]==0)
            {
                if(i>0&&arr[i-1][j]!=0)
                {
                    for(int m=i;m>0;m--)
                    {
                        arr[m][j]=arr[m-1][j];
                        arr[m-1][j]=0;
                    }
                }
                temp.push_back(i);
                temp.push_back(j);
            }
        }

    }
    return temp;

}
int find(int **arr,int posx,int posy,int point)
{
    int points=point;
    int type=arr[posx][posy];

    if(type==0)
    {
        return 0;
    }

    int upNum=1;
    for(int i=1;i<=4;++i)
    {
        if(posx-i>=0&&arr[posx-i][posy]==type&&upNum<=5)
        {
            upNum++;
        }
        else
        {
            break;
        }
    }

    int rightNum=1;
    for(int i=1;i<=4;++i)
    {
        if(posy+i<N&&arr[posx][posy+i]==type&&rightNum<=5)
        {
            rightNum++;
        }
        else
        {
            break;
        }
    }

    int downNum=1;
    for(int i=1;i<=4;++i)
    {
        if(posx+i<M&&arr[posx+i][posy]==type&&downNum<=5)
        {
            downNum++;
        }
        else
        {
            break;
        }
    }

    int leftNum=1;
    for(int i=1;i<=4;++i)
    {
        if(posy-i>=0&&arr[posx][posy-i]==type&&leftNum<=5)
        {
            leftNum++;
        }
        else
        {
            break;
        }
    }

    if(leftNum+rightNum-1>=3)
    {
        for(int i=0;i<leftNum;++i)
        {
            arr[posx][posy-i]=0;
        }
        for(int i=0;i<rightNum;++i)
        {
            arr[posx][posy+i]=0;
        }

        leftNum=leftNum+rightNum-1;
        rightNum=1;
    }
    if(upNum+downNum-1>=3)
    {
        for(int i=0;i<downNum;++i)
        {
            arr[posx+i][posy]=0;
        }

        for(int i=0;i<upNum;++i)
        {
            arr[posx-i][posy]=0;
        }

        upNum=upNum+downNum-1;
        downNum=1;
    }

    points=calculatePoints(leftNum,downNum,rightNum,upNum);

    if(points>0)
    {
        vector<int> temp=reset(arr);
        for(int i=0;i<temp.size();i=i+2)
        {
            points+=find(arr,temp.at(i),temp.at(i+1),0);
        }
    }



    return points;


}

int calculatePoints(int leftNum,int downNum,int rightNum,int upNum)
{
    int points=0;
    switch(leftNum)
    {
        case 3:
            points+=1;
            break;
        case 4:
            points+=4;
            break;
        case 5:
            points+=10;
            break;
        default:
            break;
    }

    switch(downNum)
    {
        case 3:
            points+=1;
            break;
        case 4:
            points+=4;
            break;
        case 5:
            points+=10;
            break;
        default:
            break;
    }

    switch(rightNum)
    {
        case 3:
            points+=1;
            break;
        case 4:
            points+=4;
            break;
        case 5:
            points+=10;
            break;
        default:
            break;
    }

    switch(upNum)
    {
        case 3:
            points+=1;
            break;
        case 4:
            points+=4;
            break;
        case 5:
            points+=10;
            break;
        default:
            break;
    }

    return points;
}

void swap(int **arr,int x1,int y1,int x2,int y2)
{
    int temp=arr[x1][y1];
    arr[x1][y1]=arr[x2][y2];
    arr[x2][y2]=temp;
}

void K1(int **arr)
{
    int maxPoints=0;
    int lefPoint=0;
    int rightPoint=0;
    int upPoint=0;
    int downPoint=0;
    for(int i=0;i<M;++i)
    {
        for(int j=0;j<N-1;++j)
        {
            cout<<i<<" "<<j<<endl;
            swap(arr,i,j,i,j+1);
            int **copyarr=clone(arr);
            lefPoint=find(copyarr,i,j,0);
            rightPoint=find(copyarr,i,j+1,0);
            delete[] copyarr;
            if(lefPoint+rightPoint>maxPoints)
            {
                maxPoints=lefPoint+rightPoint;
            }
            swap(arr,i,j,i,j+1);
        }
    }

    for(int i=0;i<M-1;++i)
    {
        for(int j=0;j<N;++j)
        {
            cout<<i<<" "<<j<<endl;
            swap(arr,i,j,i+1,j);
            int **copyarr=clone(arr);
            downPoint=find(copyarr,i,j,0);

            upPoint=find(copyarr,i+1,j,0);
            delete[] copyarr;
            if(upPoint+downPoint>maxPoints)
            {
                maxPoints=upPoint+downPoint;
            }
            swap(arr,i,j,i+1,j);
        }
    }

    cout<<maxPoints<<endl;
}

int **clone(int **oarr)
{
    int **copyarr=new int*[M];
    for(int i=0;i<M;++i)
    {
        copyarr[i]=new int[N];
    }
    for(int i=0;i<M;++i)
    {
        for(int j=0;j<N;++j)
        {
            copyarr[i][j]=oarr[i][j];
        }
    }

    return copyarr;
}
// void KN(int **arr,int n,int initpoint)
// {
//     int totalp=initpoint;
//     int lp=0;
//     int rp=0;
//     int up=0;
//     int dp=0;


//     if(n==0)
//     {
//         return;
//     }

//     for(int i=0;i<M;++i)
//     {
//         for(int j=0;j<N-1;++j)
//         {
//             if(arr[i][j]==0||arr[i][j+1]==0)
//             {
//                 continue;
//             }
//             swap(arr,i,j,i,j+1);
//             int **copyarr=clone(arr);
//             lp=find(copyarr,i,j,0);
//             rp=find(copyarr,i,j+1,0);
//             if(lp+rp>0)
//             {
//                 KN(copyarr,n-1,totalp+lp+rp);
//                 if(maxp<totalp+lp+rp)
//                 {
//                     display(copyarr);
//                     maxp=totalp+lp+rp;
//                 }
//             }
//             delete[] copyarr;
//             swap(arr,i,j,i,j+1);
//         }
//     }

//     for(int i=0;i<M-1;++i)
//     {
//         for(int j=0;j<N;++j)
//         {
//             if(arr[i][j]==0||arr[i+1][j]==0)
//             {
//                 continue;
//             }
//            swap(arr,i,j,i+1,j);
//             int **copyarr=clone(arr);
//             up=find(copyarr,i,j,0);
//             dp=find(copyarr,i+1,j,0);
//             if(up+dp>0)
//             {
//                 KN(copyarr,n-1,totalp+up+dp);
//                 if(maxp<totalp+up+dp)
//                 {
//                     display(copyarr);
//                     maxp=totalp+up+dp;
//                 }
//             }
//             delete[] copyarr;
//             swap(arr,i,j,i+1,j);
//         }
//     }


// }
void KN()
{
    tik=0;
    while(!stackmap.empty())
    {
        int lp=0;
        int rp=0;
        int up=0;
        int dp=0;
        int num=stackmap.top().num;
        int **arr=stackmap.top().map;
        int totalp=stackmap.top().point;
        stackmap.pop();
        if(num==0)
        {
            continue;
        }
        tik++;
        for(int i=0;i<M;++i)
        {
            for(int j=0;j<N-1;++j)
            {
                if(arr[i][j]==0||arr[i][j+1]==0)
                {
                    continue;
                }
                swap(arr,i,j,i,j+1);
                int **copyarr=clone(arr);
                lp=find(copyarr,i,j,0);
                rp=find(copyarr,i,j+1,0);
                if(lp+rp>0)
                {
                    stackmap.push(StepMap(totalp+lp+rp,copyarr,num-1));
                    if(maxp<totalp+lp+rp)
                    {
                        display(copyarr);
                        maxp=totalp+lp+rp;
                    }
                }
                swap(arr,i,j,i,j+1);
            }
        }

        for(int i=0;i<M-1;++i)
        {
            for(int j=0;j<N;++j)
            {
                if(arr[i][j]==0||arr[i+1][j]==0)
                {
                    continue;
                }
                swap(arr,i,j,i+1,j);
                int **copyarr=clone(arr);
                up=find(copyarr,i,j,0);
                dp=find(copyarr,i+1,j,0);
                if(up+dp>0)
                {
                    stackmap.push(StepMap(totalp+up+dp,copyarr,num-1));
                    if(maxp<totalp+up+dp)
                    {
                        display(copyarr);
                        maxp=totalp+up+dp;
                    }
                }
                swap(arr,i,j,i+1,j);
            }
        }
        delete[] arr;
    }

}

string getString(int **arr,int n)
{
    string s="";
    for(int i=0;i<M;++i)
    {
        for(int j=0;j<N;++j)
        {
            if(arr[i][j]==0)
            {
                s+='0';
            }
            else
            {
                s+='1';
            }
        }
    }
    return s+to_string(n);

}

bool check(string s,vector<string> &vs)
{
    bool isHave= false;
    for(int i=0;i<vs.size();++i)
    {
        if(vs.at(i)==s)
        {
            isHave= true;
            break;
        }
    }
    return isHave;
}

void KN_y()
{
    tik=0;
    vector<string> mapVec;
    while(!stackmap.empty())
    {
        int lp=0;
        int rp=0;
        int up=0;
        int dp=0;
        int num=stackmap.top().num;
        int **arr=stackmap.top().map;
        int totalp=stackmap.top().point;
        stackmap.pop();
        if(num==0)
        {
            continue;
        }
        string temp=getString(arr,num);
        if(!check(temp,mapVec))
        {
            mapVec.push_back(temp);
        } else
        {
            continue;
        }
        tik++;
        for(int i=0;i<M;++i)
        {
            for(int j=0;j<N-1;++j)
            {
                if(arr[i][j]==0||arr[i][j+1]==0)
                {
                    continue;
                }
                swap(arr,i,j,i,j+1);
                int **copyarr=clone(arr);
                swap(arr,i,j,i,j+1);
                lp=find(copyarr,i,j,0);
                rp=find(copyarr,i,j+1,0);
                if(lp+rp>0)
                {
                    stackmap.push(StepMap(totalp+lp+rp,copyarr,num-1));
                    if(maxp<totalp+lp+rp)
                    {
                        display(copyarr);
                        maxp=totalp+lp+rp;
                    }
                }
            }
        }

        for(int i=0;i<M-1;++i)
        {
            for(int j=0;j<N;++j)
            {
                if(arr[i][j]==0||arr[i+1][j]==0)
                {
                    continue;
                }
                swap(arr,i,j,i+1,j);
                int **copyarr=clone(arr);
                swap(arr,i,j,i+1,j);
                up=find(copyarr,i,j,0);
                dp=find(copyarr,i+1,j,0);
                if(up+dp>0)
                {
                    stackmap.push(StepMap(totalp+up+dp,copyarr,num-1));
                    if(maxp<totalp+up+dp)
                    {
                        display(copyarr);
                        maxp=totalp+up+dp;
                    }
                }
            }
        }
        delete[] arr;
    }

}
