
#include "fun.h"
//#include "airportrunway.h"
#include "common/common.h"
#include "stru.h"

#include <time.h>
#include <cmath>
#include <math.h>
#include <vector>
#include <algorithm>
#include <list>
#include <iostream>
#define pi 3.1415926535898
#define EarthRadius 6371.393
#define BIG 999999999 ////INT_MAX=2147483647,INT_MIN=-2147483648
//template <typename T>

using namespace std;

fun::fun()
{
    ///////很关键，不加会影响随机数的产生/////////
    unsigned seed;//
    seed=time(0);//
    srand(seed);//
    ///////很关键，不加会影响随机数的产生/////////
}


int fun::get_Clustering_Rand(int numUAV, int numTar, int &col, double **arr2_groupTar)
{
    //step1:创建一个二维数组，用于存储目标编号的随机数（第1列是目标编号，第2列是随机数）
    double **arr2_temp1=common::allocationTwoDimensionArray(numTar,2);//存储目标编号和随机数的一个二维数组
    for(int j=0;j<2;j++)
    {
        for(int i=0;i<numTar;i++)
        {
            arr2_temp1[i][0]=i+1;//i+1+numUAV;
            arr2_temp1[i][1]=common::get_RandNumberBtwMinAndMax_OneDouble(1,10);
        }
    }
    //    for(int i=0;i<numTar;i++)
    //    {
    //        for(int j=0;j<2;j++)
    //        {
    //            cout<<arr2_temp1[i][j]<<"  ";
    //        }
    //        cout<<endl;
    //    }
    cout<<"####################################"<<endl;
    //step2:将step1生成的数组按照第2列的随机数进行排序（升序或降序）
    common::quickSort_asc(arr2_temp1,0,numTar-1,1);//对第2列升序
    //common::quickSort_dsc(arr2_temp1,0,numTar-1,1);//对第2列降序
    //    for(int i=0;i<numTar;i++)
    //    {
    //        for(int j=0;j<2;j++)
    //        {
    //            cout<<arr2_temp1[i][j]<<"  ";
    //        }
    //        cout<<endl;
    //    }
    //    cout<<"#########After sort##################"<<endl;
    //step3:创建一个二维数组，将随机排序后的目标编号分组存入该二维数组，二维数组的行数是无人机数量，列数是ceil(目标数量/无人机数量)
    int eachNumUp=int(ceil((1.0*numTar)/numUAV));
    int eachNumLow=int(floor((1.0*numTar)/numUAV));
    //    cout<<"eachNumUp="<<eachNumUp<<endl;
    //    cout<<"eachNumLow="<<eachNumLow<<endl;
    double **arr2_temp2=common::allocationTwoDimensionArray(numUAV,eachNumLow);//存储分组后的目标编号，行数等于无人机数量，列数是ceil(目标数量/无人机数量)
    for(int k=0;k<numUAV;k++)
    {
        for(int j=0;j<eachNumLow;j++)
        {
            arr2_temp2[k][j]=arr2_temp1[k*eachNumLow+j][0];//将随机排序后的目标编号分组存入该二维数组
        }
    }
    //    cout<<"///////////////////////"<<endl;
    //    for(int i=0;i<numUAV;i++)
    //    {
    //        for(int j=0;j<eachNumLow;j++)
    //        {
    //            cout<<arr2_temp2[i][j]<<"  ";
    //        }
    //        cout<<endl;
    //    }
    //step4:首先判断目标编号是否分配完毕，若分配完毕，则生成最终的分组矩阵；若尚未分配完毕，则用list存储并添加剩余的目标编号到最终的分组矩阵
    int surplusNum=numTar-numUAV*eachNumLow;
    //    cout<<"surplusNum=="<<surplusNum<<endl;
    if(surplusNum==0)//目标编号全部分配完毕
    {
        col=eachNumLow;
        for(int i=0;i<numUAV;i++)
        {
            for(int j=0;j<col;j++)
            {
                arr2_groupTar[i][j]=arr2_temp2[i][j];
            }
        }
        cout<<"=========just right========="<<endl;
        for(int i=0;i<numUAV;i++)
        {
            for(int j=0;j<col;j++)
            {
                cout<<arr2_groupTar[i][j]<<"  ";
            }
            cout<<endl;
        }
    }
    else//目标编号尚未全部分配完毕
    {
        col=surplusNum+eachNumLow;
        double **arr2_group2=common::allocationTwoDimensionArray(numUAV,col);
        list<double>list_1;
        int tempCount=0;
        for(int i=numTar-1;i>=0;i--)
        {
            list_1.push_front(arr2_temp1[i][0]);
            tempCount++;
            if(tempCount==surplusNum)
            {
                break;
            }
        }
        int nTotal=list_1.size();
        //        cout<<"nTotal=="<<nTotal<<endl;
        list<double>::iterator it1=list_1.begin();
        double *arr1_temp1=common::allocationOneDimensionArray(nTotal);
        int index_section=0;
        while(it1!=list_1.end())//
        {
            arr1_temp1[index_section]=(*it1);
            // cout<<(*it1)<<"  "<<endl;
            it1++;
            index_section++;
        }
        //        for(int i=0;i<nTotal;i++)
        //        {
        //            cout<<arr1_temp1[i]<<endl;//cout<<ans_Dijkstra[i]<<"<-";
        //        }
        for(int i=0;i<numUAV;i++)
        {
            for(int j=0;j<eachNumLow;j++)//arr2_temp2
            {
                arr2_group2[i][j]=arr2_temp2[i][j];
            }
        }
        for(int j=eachNumLow;j<col;j++)
        {
            arr2_group2[0][j]=arr1_temp1[j-eachNumLow];
        }

        for(int i=0;i<numUAV;i++)
        {
            for(int j=0;j<col;j++)
            {
                arr2_groupTar[i][j]=arr2_group2[i][j];
            }
        }
        cout<<"=========not yet========="<<endl;
        for(int i=0;i<numUAV;i++)
        {
            for(int j=0;j<col;j++)
            {
                cout<<arr2_groupTar[i][j]<<"  ";
            }
            cout<<endl;
        }
    }
    return 1;
}

///
/// \brief fun::get_Clustering_DistancePrior
/// \param numUAV
/// \param numTar
/// \param arr2_coorUAV
/// \param arr2_coorTar
/// \param col
/// \param vec2
/// \return
///
//int fun::get_Clustering_DistancePrior(int numUAV, int numTar,
//                                      double **arr2_coorUAV, double **arr2_coorTar,
//                                      int &col, vector<vector<double> > &vec2)
//{
//    //保存每个目标点到最近的无人机起飞的的距离和编号的二维数组，第0列是目标编号，第1列是最近距离，第2列是离该目标最近的无人机起飞点编号
//    double **arr2_nearDis=common::allocationTwoDimensionArray(numTar,3);

//    //    double **//对arr2_coorTar进行随机排序
//    double **arr2_coorTarNew=common::allocationTwoDimensionArray(numTar,4);//最后一列存随机数
//    for(int i=0;i<numTar;i++)
//    {
//        for(int j=0;j<3;j++)
//        {
//            arr2_coorTarNew[i][j]=arr2_coorTar[i][j];
//        }
//        arr2_coorTarNew[i][3]=common::get_RandNumberBtwMinAndMax_OneDouble(1,10);
//    }
//    common::quickSort_asc(arr2_coorTarNew,0,numTar-1,3);//对第4列升序
//    //保存每个目标点分别到每个无人机起飞点的距离
//    double **arr2_eachDis=common::allocationTwoDimensionArray(numTar,numUAV);
//    for(int i=0;i<numTar;i++)
//    {
//        double x1=arr2_coorTarNew[i][1];
//        double y1=arr2_coorTarNew[i][2];
//        double dis=BIG;
//        for(int j=0;j<numUAV;j++)
//        {
//            double x2=arr2_coorUAV[j][1];
//            double y2=arr2_coorUAV[j][2];
//            arr2_eachDis[i][j]=common::get_Distance(x1,y1,x2,y2);
//            if(arr2_eachDis[i][j]<dis)
//            {
//                dis=arr2_eachDis[i][j];
//            }
//        }
//        arr2_nearDis[i][1]=dis;
//        //        cout<<"arr2_nearDis=="<<arr2_nearDis[i][1]<<endl;
//    }
//    //    cout<<"--------------------------------------------"<<endl;
//    for(int i=0;i<numTar;i++)
//    {
//        arr2_nearDis[i][0]=i+1;
//        for(int j=0;j<numUAV;j++)
//        {
//            if(arr2_nearDis[i][1]==arr2_eachDis[i][j])
//            {
//                arr2_nearDis[i][2]=j+1;
//            }
//            //            cout<<arr2_eachDis[i][j]<<",";
//        }
//        //        cout<<endl;
//    }
//    //    cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
//    //    for(int i=0;i<numTar;i++)
//    //    {
//    //        for(int j=0;j<3;j++)
//    //        {
//    //            cout<<arr2_nearDis[i][j]<<",";
//    //        }
//    //        cout<<endl;
//    //    }

//    //    common::quickSort_asc(arr2_nearDis,0,numTar-1,2);//按照第3列进行升序排序
//    //    vector<vector<double>>vec2;
//    vector<double>vec1;
//    double *arr1_UavCode=common::allocationOneDimensionArray(numUAV);
//    for(int i=0;i<numUAV;i++)
//    {
//        arr1_UavCode[i]=i+1;
//    }
//    for(int k=0;k<numUAV;k++)
//    {
//        double test=arr1_UavCode[k];
//        for(int i=0;i<numTar;i++)
//        {
//            if(arr2_nearDis[i][2]==test)
//            {
//                vec1.push_back(arr2_nearDis[i][0]);
//            }
//        }
//        vec2.push_back(vec1);
//        vec1.clear();
//    }
//    //按下标遍历
//    //    for (int i=0; i<vec2.size(); i++)
//    //    {
//    //        for(int j=0; j<vec2[i].size(); j++)
//    //        {
//    //            cout << vec2[i][j] << " ";
//    //        }
//    //        cout << endl;
//    //    }
//    int sizeCol=0;//获取二维vector列数的最大值
//    for (int i=0; i<vec2.size(); i++)
//    {
//        //        cout << "sizeCol==="<<vec2[i].size()<<endl;
//        if(vec2[i].size()>sizeCol)
//        {
//            sizeCol=vec2[i].size();
//        }
//    }
//    //    cout << "MaxsizeCol==="<<sizeCol<<endl;
//    //    cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
//    col=sizeCol;
//    for (int i=0; i<vec2.size(); i++)
//    {
//        for(int j=0; j<vec2[i].size(); j++)
//        {
//            //            vec2[i][j]=vec2[i][j];
//            //            cout << vec2[i][j] << " ";
//        }
//        //        cout << endl;
//    }
//    common::deleteTwoDimensionArray(arr2_nearDis,numTar);//double **arr2_nearDis=common::allocationTwoDimensionArray(numTar,3);
//    common::deleteTwoDimensionArray(arr2_eachDis,numTar); //arr2_eachDis
//    common::deleteOneDimensionArray(arr1_UavCode);//double *arr1_UavCode=common::allocationOneDimensionArray(numUAV);
//    common::deleteTwoDimensionArray(arr2_coorTarNew,numTar);
//    return 1;
//}

int fun::get_Clustering_GreedySearch(int numUAV, int numTar, double **arr2_coorUAV, double **arr2_coorTar, vector<vector<double> > &vec2)
{
    //Step1：将坐标值赋值给结构体数组
    Point pointUAV[numUAV];
    for(int i=0;i<numUAV;i++)
    {
        pointUAV[i].code=arr2_coorUAV[i][0];
        pointUAV[i].x=arr2_coorUAV[i][1];
        pointUAV[i].y=arr2_coorUAV[i][2];
    }
    Point pointTar[numTar];
    for(int i=0;i<numTar;i++)
    {
        pointTar[i].code=arr2_coorTar[i][0];
        pointTar[i].x=arr2_coorTar[i][1];
        pointTar[i].y=arr2_coorTar[i][2];
    }

    //Step2：将结构体数组的值赋值给vector数组
    Point P1,P2;
    vector<vector<Point>>vec2_Tar(numUAV);
    vector<Point> vec1_UAV;
    for(int i=0;i<numUAV;i++)
    {
        vec1_UAV.push_back(pointUAV[i]);
    }
    vector<Point> vec1_Tar;
    for(int i=0;i<numTar;i++)
    {
        vec1_Tar.push_back(pointTar[i]);
    }

    //Step3：确定离每个场站最近的一个点，并将其赋值到vector vec2_Tar的每行的第1个元素位置
    int index1=0;
    for(auto it=vec1_UAV.begin();it!=vec1_UAV.end();it++,index1++)
    {
        P1=(*it);
        int tmpIndex=0;
        int code;//记录符合条件的point的编号
        double tmp=999999999999.99;
        //        vector<Point> vec1_tmp;
        for(auto it2=vec1_Tar.begin();it2!=vec1_Tar.end();it2++)
        {
            P2=(*it2);//double get_Dis(Point P1,Point P2);//计算P1和P2两点之间的距离
            tmpIndex++;
            double tmpDis=get_Dis(P1,P2);
            //            cout<<(*it2).code<<" tmpDis==="<<tmpDis<<endl;
            if(tmpDis<tmp)
            {
                tmp=tmpDis;
                code=(*it2).code;
            }
        }
        //        cout<<"min==="<<tmp<<endl;
        //        cout<<"code=="<<code<<endl;
        int pos=0;

        for(auto it2=vec1_Tar.begin();it2!=vec1_Tar.end();it2++,pos++)
        {
            if((*it2).code==code)
            {
                break;
            }
        }
        //        cout<<"pos==="<<pos<<endl;
        Point P_tmp;
        P_tmp=vec1_Tar.at(pos);
        //        cout<<"P_tmp.code=="<<P_tmp.code<<endl;
        vec2_Tar[index1].push_back(P_tmp);
        vector<Point> ::iterator it3=vec1_Tar.begin();
        vec1_Tar.erase(it3+pos);
    }


    //Step4：将vec1_Tar中的元素分别添加到vec2_Tar中
    vector<Point> ::iterator it=vec1_Tar.begin();
    while(it!=vec1_Tar.end())//
    {
        for(int i=0;i<numUAV;i++)
        {
            Point P3,P4;
            P3=vec2_Tar[i][vec2_Tar[i].size()-1];//vec2_Tar的第i行的最新一个元素
            //            cout<<"P3.code"<<P3.code<<endl;
            int code;//记录符合条件的point的编号
            double tmp=999999999999.99;
            for(auto it2=vec1_Tar.begin();it2!=vec1_Tar.end();it2++)
            {
                P4=(*it2);
                double tmpDis=get_Dis(P3,P4);
                if(tmpDis<tmp)
                {
                    tmp=tmpDis;
                    code=(*it2).code;
                }
            }
            int pos=0;
            for(auto it2=vec1_Tar.begin();it2!=vec1_Tar.end();it2++,pos++)
            {
                if((*it2).code==code)
                {
                    break;
                }
            }

            //            cout<<"pos==="<<pos<<endl;
            //            cout<<"vec1_Tar.size==="<<vec1_Tar.size()<<endl;
            if(vec1_Tar.size()==0)
            {
                break;
            }
            Point P_tmp;

            P_tmp=vec1_Tar.at(pos);
            vec2_Tar[i].push_back(P_tmp);
            vector<Point> ::iterator it3=vec1_Tar.begin();
            vec1_Tar.erase(it3+pos);
        }
    }

    //迭代器打印
    vector<Point> vec_tmp;
    for(auto iter = vec2_Tar.begin(); iter != vec2_Tar.end(); iter++)
    {
        vec_tmp = *iter;
        vector<double> v1_tmp;
        for(auto it = vec_tmp.begin(); it != vec_tmp.end(); it++)
        {
//            cout << (*it).code << " ";
            v1_tmp.push_back((*it).code);
        }
        vec2.push_back(v1_tmp);
        v1_tmp.clear();

//        cout << endl;
    }
    return 1;
}

int fun::get_Clustering_DistancePrior2(int numUAV, int numTar,
                                       double **arr2_coorUAV, double **arr2_coorTar,
                                       vector<vector<double> > &vec2)
{
    //Step1：将UAV起点坐标和目标点坐标存为Point结构体数组
    Point pointUAV[numUAV];
    for(int i=0;i<numUAV;i++)
    {
        pointUAV[i].code=arr2_coorUAV[i][0];
        pointUAV[i].x=arr2_coorUAV[i][1];
        pointUAV[i].y=arr2_coorUAV[i][2];
    }
    Point pointTar[numTar];
    for(int i=0;i<numTar;i++)
    {
        pointTar[i].code=arr2_coorTar[i][0];
        pointTar[i].x=arr2_coorTar[i][1];
        pointTar[i].y=arr2_coorTar[i][2];
    }
    //Step2：将结构体数组的值赋值给vector数组
    Point P1,P2;
    vector<vector<Point>>vec2_Tar(numUAV);
    vector<Point> vec1_UAV;
    for(int i=0;i<numUAV;i++)
    {
        vec1_UAV.push_back(pointUAV[i]);
    }
    vector<Point> vec1_Tar;
    for(int i=0;i<numTar;i++)
    {
        vec1_Tar.push_back(pointTar[i]);
    }
    /////////////
    vector<Point> ::iterator it=vec1_Tar.begin();
    while(it!=vec1_Tar.end())//
    {
        int index1=0;
        for(auto it=vec1_UAV.begin();it!=vec1_UAV.end();it++,index1++)
        {
            P1=(*it);
            int tmpIndex=0;
            int code;//记录符合条件的point的编号
            double tmp=999999999999.99;
            //        vector<Point> vec1_tmp;
            for(auto it2=vec1_Tar.begin();it2!=vec1_Tar.end();it2++)
            {
                P2=(*it2);//double get_Dis(Point P1,Point P2);//计算P1和P2两点之间的距离
                tmpIndex++;
                double tmpDis=get_Dis(P1,P2);
                //            cout<<(*it2).code<<" tmpDis==="<<tmpDis<<endl;
                if(tmpDis<tmp)
                {
                    tmp=tmpDis;
                    code=(*it2).code;
                }
            }
            //        cout<<"min==="<<tmp<<endl;
            //        cout<<"code=="<<code<<endl;
            int pos=0;

            for(auto it2=vec1_Tar.begin();it2!=vec1_Tar.end();it2++,pos++)
            {
                if((*it2).code==code)
                {
                    break;
                }
            }
            if(vec1_Tar.size()==0)
            {
                break;
            }
            //        cout<<"pos==="<<pos<<endl;
            Point P_tmp;
            P_tmp=vec1_Tar.at(pos);
            //        cout<<"P_tmp.code=="<<P_tmp.code<<endl;
            vec2_Tar[index1].push_back(P_tmp);
            vector<Point> ::iterator it3=vec1_Tar.begin();
            vec1_Tar.erase(it3+pos);
        }

    }//while循环结束
    //迭代器打印
    vector<Point> vec_tmp;
    for(auto iter = vec2_Tar.begin(); iter != vec2_Tar.end(); iter++)
    {
        vec_tmp = *iter;
        vector<double> v1_tmp;
        for(auto it = vec_tmp.begin(); it != vec_tmp.end(); it++)
        {
//            cout << (*it).code << " ";
            v1_tmp.push_back((*it).code);
        }
        vec2.push_back(v1_tmp);
        v1_tmp.clear();

//        cout << endl;
    }



    return 1;
}

int fun::get_Clustering_Rand2(int numUAV, int numTar, vector<vector<double> > &vec2)
{
    //step1:确定每组目标的数量，并存于数组arr1_num中
    int *arr1_num=common::allocationOneDimensionArray_int(numUAV);
    int eachNumUp=fabs((1.0*numTar)/numUAV);
    //    cout<<"ceil==="<<eachNumUp<<endl;
    int eachNumLow=int(floor((1.0*numTar)/numUAV));
    int surplusNum=numTar-numUAV*eachNumLow;
    for(int i=0;i<numUAV;i++)
    {
        arr1_num[i]=eachNumUp;
    }
    if(surplusNum!=0)//未分配完毕
    {
        arr1_num[numUAV-1]=eachNumUp+surplusNum;
    }
    //    for(int i=0;i<numUAV;i++)
    //    {
    //        cout<<"arr1_num[i]"<<arr1_num[i]<<endl;
    //    }
    //step2:创建一个二维数组，用于存储目标编号的随机数（第1列是目标编号，第2列是随机数）
    double **arr2_temp1=common::allocationTwoDimensionArray(numTar,2);//存储目标编号和随机数的一个二维数组
    for(int i=0;i<numTar;i++)
    {
        arr2_temp1[i][0]=i+1;//i+1+numUAV;
        arr2_temp1[i][1]=common::get_RandNumberBtwMinAndMax_OneDouble(1,10);
    }
    //step2:将step1生成的数组按照第2列的随机数进行排序（升序或降序）
    common::quickSort_asc(arr2_temp1,0,numTar-1,1);//对第2列升序
    //    cout<<"Print sort"<<endl;
    //    for(int i=0;i<numTar;i++)
    //    {
    //        cout<<arr2_temp1[i][0]<<"  "<<arr2_temp1[i][1]<<endl;
    //    }
    //    cout<<"After sort"<<endl;
    //step3:将step2排序后的数组的第1列（编号）逐一赋值给vector vec1,当vec1存的元素数量满足arr1_num（每组无人机需访问的目标数量）要求时，将vec1赋值给vec2
    vector<double> vec1;
    int index=0;
    for(int k=0;k<numUAV;k++)
    {
        int cumm=0;
        for(int i=index;i<numTar;i++)
        {
            vec1.push_back(arr2_temp1[i][0]);
            cumm++;
            index++;
            if(cumm==arr1_num[k])
            {
                vec2.push_back(vec1);
                vec1.clear();
                //                cout<<"index=="<<index<<endl;
                break;
            }
        }
    }
    //    for (int i=0; i<vec2.size(); i++)
    //    {
    //        for(int j=0; j<vec2[i].size(); j++)
    //        {
    //            cout << vec2[i][j] << " ";
    //        }
    //        cout << endl;
    //    }
    common::deleteTwoDimensionArray(arr2_temp1,numTar);
    common::deleteOneDimensionArray_int(arr1_num);
    return 1;
}



//int fun::get_Routing_Rand(int numUAV,int numTar,int &col,double **arr2_groupTar,double **arr2_route)
//{
//    //double **arr2_temp1=common::allocationTwoDimensionArray();
//    for(int i=0;i<numUAV;i++)
//    {
//        list<double>list_1;
//        for(int j=0;j<numTar;j++)
//        {
//            if(arr2_groupTar[i][j]!=0.0)
//            {
//                list_1.push_back(arr2_groupTar[i][j]);
//            }
//            else
//            {
//                break;
//            }
//        }
//        int nTotal=list_1.size();
//        list<double>::iterator it1=list_1.begin();
//        double *arr1_temp1=common::allocationOneDimensionArray(nTotal);
//        int index_section=0;
//        while(it1!=list_1.end())//
//        {
//            arr1_temp1[index_section]=(*it1);
//            // cout<<(*it1)<<"  "<<endl;
//            it1++;
//            index_section++;
//        }

//        double **arr2_temp1=common::allocationTwoDimensionArray(nTotal,2);//第1列存目标编号，，第2列存随机数
//        for(int j=0;j<nTotal;j++)
//        {
//            arr2_temp1[j][0]=arr1_temp1[j];
//            arr2_temp1[j][1]=common::get_RandNumberBtwMinAndMax_OneDouble(1,10);
//        }
//        common::quickSort_asc(arr2_temp1,0,nTotal-1,1);//按照第2列进行升序
//        //common::quickSort_dsc(arr2_tempPath,0,nTotal-1,1);//按照第2列进行降序
//        //将随机排序的第i架无人机打击的目标编号赋值给二维数组arr2_route
//        for(int k=0;k<)
//    }
//    return 1;
//}








int fun::get_RoutDistance(int numUAV, int numTar,
                          double **arr2_coorUAV, double **arr2_coorTar, double **arr2_groupTar,
                          double *arr_disRout, double sumDis)
{
    Point Point_UAV[numUAV];
    for(int i=0;i<numUAV;i++)
    {
        Point_UAV[i].code=arr2_coorUAV[i][0];
        Point_UAV[i].x=arr2_coorUAV[i][1];
        Point_UAV[i].y=arr2_coorUAV[i][2];
    }

    for(int i=0;i<numUAV;i++)
    {
        list<double>list_1;
        for(int j=0;j<numTar;j++)
        {
            if(arr2_groupTar[i][j]!=0.0)
            {
                list_1.push_back(arr2_groupTar[i][j]);
            }
            else
            {
                break;
            }
        }
        int nTotal=list_1.size();
        //        cout<<"nTotal=="<<nTotal<<endl;
        list<double>::iterator it1=list_1.begin();
        double *arr1_temp1=common::allocationOneDimensionArray(nTotal);
        int index_section=0;
        while(it1!=list_1.end())//
        {
            arr1_temp1[index_section]=(*it1);
            // cout<<(*it1)<<"  "<<endl;
            it1++;
            index_section++;
        }
        Point Point_Tar[nTotal];
        for(int j=0;j<nTotal;j++)
        {
            Point_Tar[j].code=arr1_temp1[j];
            //            cout<<arr1_temp1[j]<<"---";
            //            cout<<Point_Tar[j].code<<";";
        }
        //        cout<<endl;
        //为每个点的x,y赋值
        for(int j=0;j<nTotal;j++)
        {
            double test=Point_Tar[j].code;
            for(int k=0;k<numTar;k++)
            {
                if(arr2_coorTar[k][0]==test)
                {
                    Point_Tar[j].x=arr2_coorTar[k][1];
                    Point_Tar[j].y=arr2_coorTar[k][2];
                }
            }
        }
        double tempSumTar=0.0;
        for(int j=0;j<nTotal-1;j++)
        {
            tempSumTar+=get_Dis(Point_Tar[j],Point_Tar[j+1]);
        }
        cout<<"tempSumTar==="<<tempSumTar<<endl;
        double temp1=get_Dis(Point_UAV[i],Point_Tar[0]);//第i架无人机到第1个目标点的距离
        double temp2=get_Dis(Point_UAV[i],Point_Tar[nTotal-1]);//第i架无人机到最后一个目标点的距离
        cout<<"temp1==="<<temp1<<endl;
        cout<<"temp2==="<<temp2<<endl;
        arr_disRout[i]=tempSumTar+temp1+temp2;
        cout<<"arr_disRout["<<"i"<<"]==="<<arr_disRout[i]<<endl;

        //         TEMP=temp+temp1+temp2;
    }
    double sumAll=0.0;
    for(int i=0;i<numUAV;i++)
    {
        sumAll+=arr_disRout[i];
    }
    cout<<"tempAll====="<<sumAll<<endl;
    sumDis=sumAll;
    return 1;
}

int fun::get_RoutDistance2(int numUAV, int numTar,
                           double **arr2_coorUAV, double **arr2_coorTar,
                           vector<vector<double> > vec2_group, double &sumDis, double *arr_disRout)
{
    Point Point_UAV[numUAV];
    for(int i=0;i<numUAV;i++)
    {
        Point_UAV[i].code=arr2_coorUAV[i][0];
        Point_UAV[i].x=arr2_coorUAV[i][1];
        Point_UAV[i].y=arr2_coorUAV[i][2];
    }
    for (int i=0; i<vec2_group.size(); i++)
    {
        double *arr1_temp=common::allocationOneDimensionArray(vec2_group[i].size());//存放第i组无人机负责目标的编号
        for(int j=0; j<vec2_group[i].size(); j++)
        {
            arr1_temp[j]=vec2_group[i][j];
        }
        Point Point_Tar[vec2_group[i].size()];
        for(int j=0;j<vec2_group[i].size();j++)
        {
            Point_Tar[j].code=arr1_temp[j];
        }
        //为每个点的x,y赋值
        for(int j=0;j<vec2_group[i].size();j++)
        {
            double test=Point_Tar[j].code;
            for(int k=0;k<numTar;k++)
            {
                if(arr2_coorTar[k][0]==test)
                {
                    Point_Tar[j].x=arr2_coorTar[k][1];
                    Point_Tar[j].y=arr2_coorTar[k][2];
                    break;
                }
            }
        }
        double tempSumTar=0.0;
        for(int j=0;j<vec2_group[i].size()-1;j++)
        {
            tempSumTar+=get_Dis(Point_Tar[j],Point_Tar[j+1]);
        }
        //        cout<<"tempSumTar==="<<tempSumTar<<endl;
        double temp1=get_Dis(Point_UAV[i],Point_Tar[0]);//第i架无人机到第1个目标点的距离
        double temp2=get_Dis(Point_UAV[i],Point_Tar[vec2_group[i].size()-1]);//第i架无人机到最后一个目标点的距离
        //        cout<<"temp1==="<<temp1<<endl;
        //        cout<<"temp2==="<<temp2<<endl;
        arr_disRout[i]=tempSumTar+temp1+temp2;
        //        cout<<"arr_disRout["<<"i"<<"]==="<<arr_disRout[i]<<endl;

    }
    double sumAll=0.0;
    for(int i=0;i<numUAV;i++)
    {
        sumAll+=arr_disRout[i];
    }
    //    cout<<"tempAll====="<<sumAll<<endl;
    sumDis=sumAll;
    //
    return 1;
}

///
/// \brief fun::VLSN_LocalInversion:局部翻转
/// \param vec2_group
/// \param vec2_groupNew
/// \return
///
int fun::VLSN_LocalInversion(vector<vector<double> > vec2_group, vector<vector<double> > &vec2_groupNew)
{
    for (int i=0; i<vec2_group.size(); i++)
    {
        double *arr1_temp=common::allocationOneDimensionArray(vec2_group[i].size());//存放第i组无人机负责目标的编号
        for(int j=0; j<vec2_group[i].size(); j++)
        {
            arr1_temp[j]=vec2_group[i][j];
        }
        double *arr1_temp2=common::allocationOneDimensionArray(vec2_group[i].size());//存放arr1_temp整体翻转后的数据
        int index=vec2_group[i].size()-1;
        for(int j=0; j<vec2_group[i].size(); j++)
        {
            arr1_temp2[j]=arr1_temp[index];
            index--;
        }
        arr1_temp2[0]=arr1_temp[0];
        arr1_temp2[vec2_group[i].size()-1]=arr1_temp[vec2_group[i].size()-1];
        vector<double> vec1;
        for(int k=0;k<vec2_group[i].size();k++)
        {
            vec1.push_back(arr1_temp2[k]);
        }
        vec2_groupNew.push_back(vec1);
        vec1.clear();
        common::deleteOneDimensionArray(arr1_temp);
        common::deleteOneDimensionArray(arr1_temp2);
    }
    return 1;
}

int fun::VLSN_2Exchange(vector<vector<double> > vec2_group, vector<vector<double> > &vec2_groupNew)
{
    for (int i=0; i<vec2_group.size(); i++)
    {
        double *arr1_temp=common::allocationOneDimensionArray(vec2_group[i].size());//存放第i组无人机负责目标的编号
        for(int j=0; j<vec2_group[i].size(); j++)
        {
            arr1_temp[j]=vec2_group[i][j];
        }
        int *arr1_posion=common::allocationOneDimensionArray_int(2);
        int res=get_RandNumber(2,0,vec2_group[i].size(),arr1_posion);
        // int get_RandNumber(int numRand,int minNo,int maxNo,int *arr1);//生成不重复的随机整数
        int posion1=arr1_posion[0];
        int posion2=arr1_posion[1];
        //        cout<<"Posion1=="<<posion1<<"Posion2=="<<posion2<<endl;
        double temp=arr1_temp[posion1];
        arr1_temp[posion1]=arr1_temp[posion2];
        arr1_temp[posion2]=temp;
        vector<double> vec1;
        for(int k=0;k<vec2_group[i].size();k++)
        {
            vec1.push_back(arr1_temp[k]);
        }
        vec2_groupNew.push_back(vec1);
        vec1.clear();
        common::deleteOneDimensionArray(arr1_temp);
        common::deleteOneDimensionArray_int(arr1_posion);
    }
    return 1;
}

int fun::VLSN_3Exchange(vector<vector<double> > vec2_group, vector<vector<double> > &vec2_groupNew)
{
    for (int i=0; i<vec2_group.size(); i++)
    {
        double *arr1_temp=common::allocationOneDimensionArray(vec2_group[i].size());//存放第i组无人机负责目标的编号
        for(int j=0; j<vec2_group[i].size(); j++)
        {
            arr1_temp[j]=vec2_group[i][j];
        }
        int *arr1_posion=common::allocationOneDimensionArray_int(3);
        int res=get_RandNumber(3,0,vec2_group[i].size(),arr1_posion);
        int posion1=arr1_posion[0];
        int posion2=arr1_posion[1];
        int posion3=arr1_posion[2];
        //        cout<<"  Posion1=="<<posion1<<"  Posion2=="<<posion2<<"  Posion3=="<<posion3<<endl;
        double temp=arr1_temp[posion1];
        arr1_temp[posion1]=arr1_temp[posion2];
        arr1_temp[posion2]=arr1_temp[posion3];
        arr1_temp[posion3]=temp;
        vector<double> vec1;
        for(int k=0;k<vec2_group[i].size();k++)
        {
            vec1.push_back(arr1_temp[k]);
        }
        vec2_groupNew.push_back(vec1);
        vec1.clear();
        common::deleteOneDimensionArray(arr1_temp);
        common::deleteOneDimensionArray_int(arr1_posion);
    }
    return 1;
}

void fun::VLSN_LocalInversion2(vector<vector<double> > &vec2_Tar)
{
    vector<vector<double> > vec2;
    for (int i=0; i<vec2_Tar.size(); i++)
    {
        double *arr1_temp=common::allocationOneDimensionArray(vec2_Tar[i].size());//存放第i组无人机负责目标的编号
        for(int j=0; j<vec2_Tar[i].size(); j++)
        {
            arr1_temp[j]=vec2_Tar[i][j];
        }
        double *arr1_temp2=common::allocationOneDimensionArray(vec2_Tar[i].size());//存放arr1_temp整体翻转后的数据
        int index=vec2_Tar[i].size()-1;
        for(int j=0; j<vec2_Tar[i].size(); j++)
        {
            arr1_temp2[j]=arr1_temp[index];
            index--;
        }
        arr1_temp2[0]=arr1_temp[0];
        arr1_temp2[vec2_Tar[i].size()-1]=arr1_temp[vec2_Tar[i].size()-1];
        vector<double> vec1;
        for(int k=0;k<vec2_Tar[i].size();k++)
        {
            vec1.push_back(arr1_temp2[k]);
        }
        vec2.push_back(vec1);
        vec1.clear();
        common::deleteOneDimensionArray(arr1_temp);
        common::deleteOneDimensionArray(arr1_temp2);
    }
    for (int i=0; i<vec2.size(); i++)
    {
        for(int j=0; j<vec2[i].size(); j++)
        {
            vec2_Tar[i][j]=vec2[i][j];
            //            cout << vec2[i][j] << " ";
        }
        //        cout << endl;
    }
}

void fun::VLSN_2Exchange2(vector<vector<double> > &vec2_Tar)
{
    vector<vector<double> > vec2;
    for (int i=0; i<vec2_Tar.size(); i++)
    {
        double *arr1_temp=common::allocationOneDimensionArray(vec2_Tar[i].size());//存放第i组无人机负责目标的编号
        for(int j=0; j<vec2_Tar[i].size(); j++)
        {
            arr1_temp[j]=vec2_Tar[i][j];
        }
        int *arr1_posion=common::allocationOneDimensionArray_int(2);
        int res=get_RandNumber(2,0,vec2_Tar[i].size(),arr1_posion);
        // int get_RandNumber(int numRand,int minNo,int maxNo,int *arr1);//生成不重复的随机整数
        int posion1=arr1_posion[0];
        int posion2=arr1_posion[1];
        //        cout<<"Posion1=="<<posion1<<"Posion2=="<<posion2<<endl;
        double temp=arr1_temp[posion1];
        arr1_temp[posion1]=arr1_temp[posion2];
        arr1_temp[posion2]=temp;
        vector<double> vec1;
        for(int k=0;k<vec2_Tar[i].size();k++)
        {
            vec1.push_back(arr1_temp[k]);
        }
        vec2.push_back(vec1);
        vec1.clear();
        common::deleteOneDimensionArray(arr1_temp);
        common::deleteOneDimensionArray_int(arr1_posion);
    }
    for (int i=0; i<vec2.size(); i++)
    {
        for(int j=0; j<vec2[i].size(); j++)
        {
            vec2_Tar[i][j]=vec2[i][j];
        }
    }
}

void fun::VLSN_3Exchange2(vector<vector<double> > &vec2_Tar)
{
    vector<vector<double> > vec2;
    for (int i=0; i<vec2_Tar.size(); i++)
    {
        double *arr1_temp=common::allocationOneDimensionArray(vec2_Tar[i].size());//存放第i组无人机负责目标的编号
        for(int j=0; j<vec2_Tar[i].size(); j++)
        {
            arr1_temp[j]=vec2_Tar[i][j];
        }
        int *arr1_posion=common::allocationOneDimensionArray_int(3);
        int res=get_RandNumber(3,0,vec2_Tar[i].size(),arr1_posion);
        int posion1=arr1_posion[0];
        int posion2=arr1_posion[1];
        int posion3=arr1_posion[2];
        //        cout<<"  Posion1=="<<posion1<<"  Posion2=="<<posion2<<"  Posion3=="<<posion3<<endl;
        double temp=arr1_temp[posion1];
        arr1_temp[posion1]=arr1_temp[posion2];
        arr1_temp[posion2]=arr1_temp[posion3];
        arr1_temp[posion3]=temp;
        vector<double> vec1;
        for(int k=0;k<vec2_Tar[i].size();k++)
        {
            vec1.push_back(arr1_temp[k]);
        }
        vec2.push_back(vec1);
        vec1.clear();
        common::deleteOneDimensionArray(arr1_temp);
        common::deleteOneDimensionArray_int(arr1_posion);
    }
    for (int i=0; i<vec2.size(); i++)
    {
        for(int j=0; j<vec2[i].size(); j++)
        {
            vec2_Tar[i][j]=vec2[i][j];
        }
    }
}

double fun::get_Dis(Point P1, Point P2)
{
    double res;
    res=sqrt(pow(fabs(P1.x-P2.x),2)+pow(fabs(P1.y-P2.y),2));
    return res;
}

int fun::DistanceGreedySearch(int numTar, double **arr2_point, double **arr2_Sequence)
{
    Point Point_Tar[numTar];
    for(int i=0;i<numTar;i++)
    {
        Point_Tar[i].code=arr2_point[i][0];
        Point_Tar[i].x=arr2_point[i][1];
        Point_Tar[i].y=arr2_point[i][2];
        //        cout<<Point_Tar[i].code<<";"<<Point_Tar[i].x<<";"<<Point_Tar[i].y<<endl;
    }
    //step1：为vector数组赋值
    vector<Point>v1;//存放原先的目标点
    vector<Point>v2;//存放贪婪搜索后的目标点顺序
    for(int i=1;i<numTar;i++)
    {
        v1.push_back(Point_Tar[i]);//v1赋初值（将Point_Tar[i]数组中从第二个元素开始，逐一赋值给v1）
    }
    v2.push_back(Point_Tar[0]);//v2赋初值（将Point_Tar[i]数组中从第一个元素值给v2）
    Point P1;//v2的第一个（最新的）元素
    Point P2;//遍历v1中剩余的元素
    for(int i=0;i<2*numTar;i++)
    {
        double tempCode=0;
        auto it2=v2.end()-1;//end指向末尾元素的下一个元素。
        P1=(*it2);//v2的第一个（最新的）元素
        double minDis=9999999999999.999;//定义一个最短距离值
        vector<int>::size_type nIndex1=0;
        for(auto it1 = v1.begin(); it1 != v1.end(); it1++,nIndex1++)
        {
            P2=(*it1);//遍历v1中剩余的所有元素
            double tempDis=get_Dis(P2,P1);//求P1到P2之间的距离
            if(tempDis<minDis )
            {
                minDis=tempDis;//更新最短距离
                tempCode=(*it1).code;//确定最短距离对应的Point的编号code
            }
            //            cout<<"v1.code="<<(*it1).code<<" tempDis=="<<tempDis<<endl;
        }
        //        cout<<"tempCode="<<tempCode<<" minDis="<<minDis<<endl;
        vector<int>::size_type tempIndex=0;//定义一个索引值tempIndex
        for(auto it1 = v1.begin(); it1 != v1.end(); it1++,tempIndex++)
        {
            if((*it1).code==tempCode)//定位v1中那个与P1点距离最短的点的编号code
            {
                P2=(*it1);//将v1中那个与P1点距离最短的点赋值给P2
                v2.push_back(P2);//将P2压入（赋值给v2）
                break;
            }
        }
        /*删除单个元素，从0开始计数，删除第二个元素
        v.erase(v.begin()+2);
          删除一段元素，删除迭代器第一到第五区间所有元素
        v.erase(v.begin()+1,v.begin()+5);*/
        //tempIndex记录了v1中符合if条件的那个点的索引号，很重要，不能删除！！！
        v1.erase(v1.begin()+tempIndex);//将v1中那个与P1点距离最短的点删除
        //        cout<<"v2.size()=="<<v2.size()<<endl;
        if(v1.size()<1)
        {
            break;
        }
    }
    //    cout<<"**************************"<<endl;
    //    for(auto it3 = v2.begin(); it3 != v2.end(); it3++)
    //    {
    //        cout<<"v2.code ="<<(*it3).code<<endl;
    //    }

    Point Point_Sequence[numTar];
    vector<int>::size_type tempIndex2=0;//定义一个索引值tempIndex
    for(auto it3 = v2.begin(); it3 != v2.end(); it3++,tempIndex2++)
    {
        Point_Sequence[tempIndex2]=(*it3);
    }
    for(int i=0;i<numTar;i++)
    {

        arr2_Sequence[i][0]=Point_Sequence[i].code;
        arr2_Sequence[i][1]=Point_Sequence[i].x;
        arr2_Sequence[i][2]=Point_Sequence[i].y;
    }
    cout<<"*********In Fun************"<<endl;
    for(int i=0;i<numTar;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<arr2_Sequence[i][j]<<"  ";
        }
        cout<<endl;
    }


    //    for (int i=0; i<v2.size(); i++)
    //    {
    //        for(int j=0; j<v2[i].size(); j++)
    //        {
    //            arr2_Sequence[i][j]=v2[i][j];
    //            cout << arr2_Sequence[i][j] << " ";
    //        }
    //        cout << endl;
    //    }
    return 1;
}

///
/// \brief fun::DistanceGreedySearch2:根据给定的目标信息，从arr2_point的第一个点出发，采用贪婪搜索思想选择离该点最近的一点访问，直到所有点访问完毕
/// \param numTar
/// \param arr2_point
/// \param vec1_Sequence
/// \return
///
int fun::DistanceGreedySearch2(int numTar, double **arr2_point, vector<double> &vec1_Sequence)
{
    Point Point_Tar[numTar];
    for(int i=0;i<numTar;i++)
    {
        Point_Tar[i].code=arr2_point[i][0];
        Point_Tar[i].x=arr2_point[i][1];
        Point_Tar[i].y=arr2_point[i][2];
        //        cout<<Point_Tar[i].code<<";"<<Point_Tar[i].x<<";"<<Point_Tar[i].y<<endl;
    }
    //step1：为vector数组赋值
    vector<Point>v1;//存放原先的目标点
    vector<Point>v2;//存放贪婪搜索后的目标点顺序
    for(int i=1;i<numTar;i++)
    {
        v1.push_back(Point_Tar[i]);//v1赋初值（将Point_Tar[i]数组中从第二个元素开始，逐一赋值给v1）
    }
    v2.push_back(Point_Tar[0]);//v2赋初值（将Point_Tar[i]数组中从第一个元素值给v2）
    Point P1;//v2的第一个（最新的）元素
    Point P2;//遍历v1中剩余的元素
    for(int i=0;i<numTar;i++)
    {
        double tempCode=0;
        auto it2=v2.end()-1;//end指向末尾元素的下一个元素。
        P1=(*it2);//v2的第一个（最新的）元素
        double minDis=9999999999999.999;//定义一个最短距离值
        vector<int>::size_type nIndex1=0;
        for(auto it1 = v1.begin(); it1 != v1.end(); it1++,nIndex1++)
        {
            P2=(*it1);//遍历v1中剩余的所有元素
            double tempDis=get_Dis(P2,P1);//求P1到P2之间的距离
            if(tempDis<minDis )
            {
                minDis=tempDis;//更新最短距离
                tempCode=(*it1).code;//确定最短距离对应的Point的编号code
            }
            //            cout<<"v1.code="<<(*it1).code<<" tempDis=="<<tempDis<<endl;
        }

        vector<int>::size_type tempIndex=0;//定义一个索引值tempIndex
        for(auto it1 = v1.begin(); it1 != v1.end(); it1++,tempIndex++)
        {
            if((*it1).code==tempCode)//定位v1中那个与P1点距离最短的点的编号code
            {
                P2=(*it1);//将v1中那个与P1点距离最短的点赋值给P2
                v2.push_back(P2);//将P2压入（赋值给v2）
                break;
            }
        }
        /*删除单个元素，从0开始计数，删除第二个元素
            v.erase(v.begin()+2);
              删除一段元素，删除迭代器第一到第五区间所有元素
            v.erase(v.begin()+1,v.begin()+5);*/
        //tempIndex记录了v1中符合if条件的那个点的索引号，很重要，不能删除！！！
        v1.erase(v1.begin()+tempIndex);//将v1中那个与P1点距离最短的点删除
        //        cout<<"v2.size()=="<<v2.size()<<endl;
        if(v1.size()<1)
        {
            break;
        }
    }
    //        vector<double>vec1;
    //    cout<<"mark"<<endl;
    vector<int>::size_type tempIndex2=0;
    for(auto it = v2.begin(); it != v2.end(); it++,tempIndex2++)
    {
        vec1_Sequence.push_back((*it).code);//=;
    }

    return 1;
}

int fun::vector2_To_array(vector<vector<double> > vec2, int &row,int &col,double **arr2)
{

    row=vec2.size();
    col=0;
    for (int i=0; i<vec2.size(); i++)
    {
        if(vec2[i].size()>col)
        {
            col=vec2[i].size();
        }
    }
    double **arr_temp=common::allocationTwoDimensionArray(row,col);

    for (int i=0; i<vec2.size(); i++)
    {
        for(int j=0; j<vec2[i].size(); j++)
        {
            arr_temp[i][j]=vec2[i][j];
            cout << arr_temp[i][j] << " ";
        }
        cout << endl;
    }



    cout<<"mark"<<endl;
    cout<<"row=="<<row<<endl;
    cout<<"col=="<<col<<endl;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            arr2[i][j]=arr_temp[i][j];

        }

    }


    return 1;
}

int fun::test_vector(int num, vector<double> &vec1)
{
    vec1.push_back(0.01);
    vec1.push_back(0.02);
    vec1.push_back(0.03);
    vec1.push_back(0.04);
    //    for(auto it1=vec1.begin();it1!=vec1.end();it1++)
    //    {
    //        cout<<(*it1)<<"  ";
    //    }
    //    cout<<endl;
    return 1;
}
/* double res;
    double m1=(double)(rand()%101)/101;
    low++;
    double m2=(double)((rand()%(up-low+1))+low);
    m2=m2-1;
    res=m1+m2;
    return res;*/
int fun::get_RandNumber(int numRand, int minNo, int maxNo, int *arr1)
{
    //    unsigned seed;//
    //    seed=time(0);//
    //    srand(seed);//
    struct timeb timeSeed;
    //    ftime(&timeSeed);
    srand(timeSeed.time *10000000000.0 + timeSeed.millitm);
    unsigned int crand = rand();

    int arr[numRand];
    //    srand((int)time(NULL));  //设置系统时间为随机种子
    for(int i=0;i<numRand;i++)
    {
        arr[i]=minNo+rand()%maxNo;
        for(int j=0;j<i;j++)
        {
            if(arr[i]==arr[j])
            {
                i--;
                break;
            }
        }
    }
    for(int i=0;i<numRand;i++)
    {
        arr1[i]=arr[i];
    }
    return 1;
}

int *fun::RandNumDiff(int numRand, int minNo, int maxNo)
{
    int *data=common::allocationOneDimensionArray_int(numRand);
    //    srand((int)time(NULL));  //设置系统时间为随机种子
    int arr[numRand];
    for(int i=0;i<numRand;i++)
    {
        arr[i]=minNo+rand()%maxNo;
        for(int j=0;j<i;j++)
        {
            if(arr[i]==arr[j])
            {
                i--;
                break;
            }
        }
    }
    for(int i=0;i<numRand;i++)
    {
        data[i]=arr[i];
    }
    return data;
}

int fun::ObjectFunction(int numUAV, int numTar,
                        double impro,
                        int iteration_all,
                        int iteration_rout,
                        int iteration_local,
                        double **arr2_coorUAV, double **arr2_coorTar,
                        double &sumDis, double *arr_disRout,vector<vector<double>>&vec2_final)
{
    double res=9999999999999.99;
    vector<vector<double>>vec2_tmp;//存储较好结果的路径
    for(int k=0;k<iteration_all;k++)
    {/*
    int get_Clustering_Rand2(int numUAV, int numTar, vector<vector<double>>&vec2);//目标聚类算法（ 随机聚类2）
    int get_Clustering_GreedySearch(int numUAV,int numTar,double **arr2_coorUAV,double **arr2_coorTar,vector<vector<double>>&vec2);//目标聚类（贪婪搜索聚类）

    int get_Clustering_DistancePrior2(int numUAV, int numTar,
                                     double **arr2_coorUAV, double **arr2_coorTar,
                                     vector<vector<double>>&vec2);//目标聚类（距离优先聚类）*/
        //Step1:目标聚类
        vector<vector<double>>vec2_Group;
        int *Jud1=RandNumDiff(1,1,3);
        int col1=0;
        //                cout<<"Jud1=="<<Jud1[0]<<endl;
        if(Jud1[0]==1)//调用“随机聚类”算子：get_Clustering_Rand2
        {
            int res1=get_Clustering_Rand2(numUAV,numTar,vec2_Group);
        }
        else if(Jud1[0]==2)//调用“距离优先聚类”算子：get_Clustering_DistancePrior
        {
            int res1=get_Clustering_GreedySearch(numUAV,numTar,arr2_coorUAV,arr2_coorTar,vec2_Group);
        }
        else if(Jud1[0]==3)//调用“距离优先聚类”算子：get_Clustering_DistancePrior
        {
            int res1=get_Clustering_DistancePrior2(numUAV,numTar,arr2_coorUAV,arr2_coorTar,vec2_Group);
        }
        //        double res2=999999999999999.0;
        //        for(int l=0;l<iteration_rout;l++)
        //        {
        //Step2:路径生成
        vector<vector<double>>vec2_Tar;
        int *Jud2=RandNumDiff(1,1,2);
        //        cout<<"Jud2=============="<<Jud2[0]<<endl;
        if(Jud2[0]==1)//调用“区域路径随机生成”算子：get_PathGeneration_Rand2
        {
            int res2=get_PathGeneration_Rand2(vec2_Group,vec2_Tar);
        }
        else if(Jud2[0]==2)//调用“区域路径最近距离优先生成”算子：get_PathGeneration_DistancePrior
        {
            int res2=get_PathGeneration_DistancePrior(numTar,arr2_coorTar,vec2_Group,vec2_Tar);
        }
        //Step3:计算路径长度,计算初始解
        double tempDis1=0.0;
        double *arr1_disRout1=common::allocationOneDimensionArray(numUAV);
        int res_dis1=get_RoutDistance2(numUAV,numTar,arr2_coorUAV,arr2_coorTar,vec2_Tar,tempDis1,arr1_disRout1);
        //        cout<<"tempDis1=="<<tempDis1<<endl;

        if(tempDis1<res)
        {
            res=tempDis1;
            vector<double> vec1_tmp;

            for(auto iter = vec2_Tar.begin(); iter != vec2_Tar.end(); iter++)
            {
                vec1_tmp = *iter;
                vec2_tmp.push_back(vec1_tmp);
            }
            vec1_tmp.clear();
        }
        cout<<res<<endl;
    }//all******************************
    //        for (int i=0; i<vec2_tmp.size(); i++)
    //        {
    //            for(int j=0; j<vec2_tmp[i].size(); j++)
    //            {
    //                cout << vec2_tmp[i][j] << " ";
    //            }
    //            cout << endl;
    //        }
    //        cout<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;

    //按下标遍历
    vector<double> vec1_tmp2;
    for (int i=vec2_tmp.size()-numUAV; i<vec2_tmp.size(); i++)
    {
        for(int j=0; j<vec2_tmp[i].size(); j++)
        {
            vec1_tmp2.push_back(vec2_tmp[i][j]);
            //                   cout << vec1_tmp2[j]<< " ";
        }
        vec2_final.push_back(vec1_tmp2);
        vec1_tmp2.clear();
        //               cout << endl;
    }

    cout<<"sumDis=="<<res<<endl;
    return 1;
}



int fun::get_PathGeneration_Rand(int numUAV, int numTar, int &col,
                                 double **arr2_groupTar, double **arr2_pathTar)
{
    vector<vector<double>>vec2;
    vector<double>vec1;
    for(int i=0;i<numUAV;i++)//numUAV
    {
        //step1:将输入的二维数组arr2_groupTar分行赋值给list_1
        list<double>list_1;
        for(int j=0;j<numTar;j++)
        {
            if(arr2_groupTar[i][j]!=0.0)
            {
                list_1.push_back(arr2_groupTar[i][j]);
            }
            else
            {
                break;
            }
        }
        //step2:再将list_1中的元素赋值给一个临时一维数组arr1_tempPath
        int nTotal=list_1.size();
        //        cout<<"nTotal=="<<nTotal<<endl;
        list<double>::iterator it1=list_1.begin();
        double *arr1_tempPath=common::allocationOneDimensionArray(nTotal);
        int index_section=0;
        while(it1!=list_1.end())//
        {
            arr1_tempPath[index_section]=(*it1);
            // cout<<(*it1)<<"  "<<endl;
            it1++;
            index_section++;
        }
        //step3:创建一个二维数组，用于存储目标编号的随机数（第1列是目标编号，第2列是随机数）
        double **arr2_tempPath=common::allocationTwoDimensionArray(nTotal,2);
        for(int k=0;k<nTotal;k++)
        {
            arr2_tempPath[k][0]=arr1_tempPath[k];
            arr2_tempPath[k][1]=common::get_RandNumberBtwMinAndMax_OneDouble(1,10);
        }
        cout<<"####################################"<<endl;
        //step4:将step3生成的数组按照第2列的随机数进行排序（升序或降序）
        common::quickSort_asc(arr2_tempPath,0,nTotal-1,1);//按照第2列进行升序
        //common::quickSort_dsc(arr2_tempPath,0,nTotal-1,1);//按照第2列进行降序
        //step5:将排序后的目标访问顺序赋值给vector vec1
        cout<<"arr2_tempPath[k][0]====="<<endl;
        for(int k=0;k<nTotal;k++)
        {
            vec1.push_back(arr2_tempPath[k][0]);
            cout<<arr2_tempPath[k][0]<<" ";
        }
        cout<<endl;
        vec2.push_back(vec1);
        vec1.clear();
    }
    //按下标遍历
    for (int i=0; i<vec2.size(); i++)
    {
        for(int j=0; j<vec2[i].size(); j++)
        {
            cout << vec2[i][j] << " ";
        }
        cout << endl;
    }
    int sizeCol=0;//获取二维vector列数的最大值
    for (int i=0; i<vec2.size(); i++)
    {
        if(vec2[i].size()>sizeCol)
        {
            sizeCol=vec2[i].size();
        }
    }
    cout << "MaxsizeCol==="<<sizeCol<<endl;
    cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
    col=sizeCol;
    for (int i=0; i<vec2.size(); i++)
    {
        for(int j=0; j<vec2[i].size(); j++)
        {
            arr2_pathTar[i][j]=vec2[i][j];
            cout << arr2_pathTar[i][j] << " ";
        }
        cout << endl;
    }

    return 1;
}

int fun::get_PathGeneration_DistancePrior(int numTar,
                                          double **arr2_coorTar,
                                          vector<vector<double>>vec2_group,
                                          vector<vector<double> > &vec2_Tar)
{
    for (int i=0; i<vec2_group.size(); i++)
    {
        double *arr1_temp=common::allocationOneDimensionArray(vec2_group[i].size());//存放第i组无人机负责目标的编号
        for(int j=0; j<vec2_group[i].size(); j++)
        {
            arr1_temp[j]=vec2_group[i][j];
        }
        double **arr2_point=common::allocationTwoDimensionArray(vec2_group[i].size(),3);
        for(int j=0; j<vec2_group[i].size(); j++)
        {
            arr2_point[j][0]=arr1_temp[j];
            for(int k=0;k<numTar;k++)
            {
                if(arr2_point[j][0]==arr2_coorTar[k][0])
                {
                    arr2_point[j][1]=arr2_coorTar[k][1];
                    arr2_point[j][2]=arr2_coorTar[k][2];
                    break;
                }
            }
        }
        vector<double>vec1_Sequence;
        int res=DistanceGreedySearch2(vec2_group[i].size(),arr2_point,vec1_Sequence);
        vec2_Tar.push_back(vec1_Sequence);
        vec1_Sequence.clear();
        common::deleteOneDimensionArray(arr1_temp);
        common::deleteTwoDimensionArray(arr2_point,vec2_group[i].size());
    }


    return 1;
}

void fun::print_vec1(vector<double> &vec)
{
    cout << "打印vector:" << endl;
    for(auto it=vec.begin();it!=vec.end();it++)
    {
        //        cout<<(*it)<<"\t";
        cout<<(*it)<<" ";
    }
    cout << endl;
}

void fun::print_vec2(vector<vector<double> > &vec2)
{
    cout << "打印vector:" << endl;
    for (int i=0; i<vec2.size(); i++)
    {
        for(int j=0; j<vec2[i].size(); j++)
        {
            cout << vec2[i][j] << " ";
        }
        cout << endl;
    }
}

//void fun::randperm(int Num)
//{

////     system("PAUSE");                     //屏幕暂停,以便看到显示结果
////     return 0;

//}

int fun::get_PathGeneration_Rand2( vector<vector<double> > vec2_group,
                                   vector<vector<double> > &vec2_Tar)
{
    //    for (int i=0; i<vec2_group.size(); i++)
    //    {
    //        for(int j=0; j<vec2_group[i].size(); j++)
    //        {
    //            cout << vec2_group[i][j] << " ";
    //        }
    //        cout << endl;
    //    }
    //    cout<<"######################################"<<endl;
    //step1:将存放分组信息的vector转化为二维数组，便于调用排序算法进行随机排序
    vector<double>vec1;
    for (int i=0; i<vec2_group.size(); i++)
    {
        //        double *arr1_temp=common::allocationOneDimensionArray(vec2_group[i].size());
        double **arr2_tempPath=common::allocationTwoDimensionArray(vec2_group[i].size(),2);
        for(int j=0; j<vec2_group[i].size(); j++)
        {
            arr2_tempPath[j][0]=vec2_group[i][j];
            arr2_tempPath[j][1]=common::get_RandNumberBtwMinAndMax_OneDouble(1,10);
        }
        //创建一个二维数组，用于存储目标编号的随机数（第1列是目标编号，第2列是随机数）



        //step5:将step4生成的数组按照第2列的随机数进行排序（升序或降序）
        common::quickSort_asc(arr2_tempPath,0,vec2_group[i].size()-1,1);//按照第2列进行升序
        //        for(int k=0;k<vec2_group[i].size();k++)
        //        {
        //            for(int j=0;j<2;j++)
        //            {
        //                cout<<arr2_tempPath[k][j]<<" ";
        //            }
        //            cout<<endl;
        //        }
        //        cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
        //step5:将排序后的目标访问顺序赋值给vector vec1
        vector<int>::size_type tempIndex=0;
        for(int k=0;k<vec2_group[i].size();k++,tempIndex++)
        {
            vec1.push_back(arr2_tempPath[k][0]);
            //                            cout<<vec1.at(tempIndex)<<"-";
        }
        vec2_Tar.push_back(vec1);
        vec1.clear();

        //        cout << endl;
    }
    //    cout<<"######################################"<<endl;
    //        vector<double>vec1;
    //        for(int i=0;i<numUAV;i++)//numUAV
    //        {
    //            //step2:将输入的二维数组arr_temp分行赋值给list_1
    //            list<double>list_1;
    //            for(int j=0;j<numTar;j++)
    //            {
    //                if(arr_temp[i][j]!=0.0)
    //                {
    //                    list_1.push_back(arr_temp[i][j]);
    //                }
    //                else
    //                {
    //                    break;
    //                }
    //            }
    //            //step3:再将list_1中的元素赋值给一个临时一维数组arr1_tempPath
    //            int nTotal=list_1.size();
    //            //        cout<<"nTotal=="<<nTotal<<endl;
    //            list<double>::iterator it1=list_1.begin();
    //            double *arr1_tempPath=common::allocationOneDimensionArray(nTotal);
    //            int index_section=0;
    //            while(it1!=list_1.end())//
    //            {
    //                arr1_tempPath[index_section]=(*it1);
    //                // cout<<(*it1)<<"  "<<endl;
    //                it1++;
    //                index_section++;
    //            }
    //            //step4:创建一个二维数组，用于存储目标编号的随机数（第1列是目标编号，第2列是随机数）
    //            double **arr2_tempPath=common::allocationTwoDimensionArray(nTotal,2);
    //            for(int k=0;k<nTotal;k++)
    //            {
    //                arr2_tempPath[k][0]=arr1_tempPath[k];
    //                arr2_tempPath[k][1]=common::get_RandNumberBtwMinAndMax_OneDouble(1,10);
    //            }
    ////            cout<<"####################################"<<endl;
    //            //step5:将step4生成的数组按照第2列的随机数进行排序（升序或降序）
    //            common::quickSort_asc(arr2_tempPath,0,nTotal-1,1);//按照第2列进行升序
    //            //common::quickSort_dsc(arr2_tempPath,0,nTotal-1,1);//按照第2列进行降序
    //            //step5:将排序后的目标访问顺序赋值给vector vec1
    //            for(int k=0;k<nTotal;k++)
    //            {
    //                vec1.push_back(arr2_tempPath[k][0]);
    ////                cout<<arr2_tempPath[k][0]<<" ";
    //            }
    ////            cout<<endl;
    //            vec2_Tar.push_back(vec1);
    //            vec1.clear();
    //        }
    return 1;
}
















