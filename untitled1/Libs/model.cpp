#include "model.h"
#include <fstream>
#include <iostream>
#include <list>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <cstdio>


Model::Model()
{
    std::cout<<"Model"<<reinterpret_cast<unsigned long >(this)<<" is created"<<std::endl;
}
Model::~Model()
{
    std::cout<<"Model "<<reinterpret_cast<unsigned long>(this)<<" is destroyed"<<std::endl;
}


ObjModel::ObjModel()
{
    face_dim=3;
}

bool ObjModel::rawload(const std::string &file_name)
{
    using namespace std;
    ifstream of;
    of.open(file_name.c_str(),ios_base::binary);
    if (!of.is_open())
    {
        std::cerr<<"Cannot find the model file: "<<file_name<<endl;
        return false;
    }
    string vmark;
    bool bFirst=true;
    int nface=1;
    list<Point3f> coord_list;
    list<Point3f> normal_list;
    list<Point2f> texture_list;
    list<rawFace> face_list;
    char temp_buf[512];
    of>>vmark;

    while(!of.eof())
    {        
        if (vmark=="v")
        {
            coord_list.push_back(Point3f());
            for (int i=0;i<3;i++)
                of>>coord_list.back()[i]  ;
            //vmark.clear();

        }else
        if (vmark=="vn"){
            normal_list.push_back(Point3f());
            for (int i=0;i<3;i++){
                of>> normal_list.back()[i]  ;
                //normal_list.back()[i]*=-1  ;
            }
            //vmark.clear();

        }else
        if (vmark=="vt"){
            texture_list.push_back(Point2f());
            for (int i=0;i<2;i++)
                of>>texture_list.back()[i]  ;
            //vmark.clear();

        }else
        if (vmark=="f"){
            if (bFirst){
                string s;
                of>>s;
                nface=1;
                for (unsigned int i=0;i<s.length();i++)
                    if (s[i]=='/') nface++;
                bFirst=false;
                of.seekg((int)of.tellg()-s.length());
            }
            char c;
            face_list.push_back(rawFace());
            for (int i=0;i<face_dim;i++){
                for (int j=0;j<nface-1;j++){
                   of>>face_list.back()[j*face_dim+i];
                   --face_list.back()[j*face_dim+i];  // index of obj starts from 1 not 0
                   of>>c;
                }
                of>>face_list.back()[(nface-1)*face_dim+i];
                --face_list.back()[(nface-1)*face_dim+i];
            }
            //vmark.clear();
       }else
            of.getline(temp_buf,512);
        of>>vmark;
    }
    std::cout<<vmark<<std::endl;
    of.close();
    verts.clear();
    texs.clear();
    norms.clear();
    rawfaces.clear();
    verts.reserve(coord_list.size());
    texs.reserve(texture_list.size());
    norms.reserve(normal_list.size());
    rawfaces.reserve(face_list.size());


    for_each(coord_list.begin(),coord_list.end(),[this](const Point3f& it){this->verts.push_back(it);});
    for_each(normal_list.begin(),normal_list.end(),[this](const Point3f& it){this->norms.push_back(it);});
    for_each(texture_list.begin(),texture_list.end(),[this](const Point2f& it){this->texs.push_back(it);});
    for_each(face_list.begin(),face_list.end(),[this](const rawFace& it){this->rawfaces.push_back(it);});

    face_properties_num=nface;
    face_num=rawfaces.size();
    vert_num=verts.size();
    tex_num=texs.size();
    norm_num=norms.size();

    return true;
}

//bool ObjModel::load(const std::string &file_name)
//{
//    using namespace std;
//    ifstream infile;
//    infile.open(file_name.c_str(),ios::binary);

//    //std::cout<<sizeof(int)<<"\t"<<sizeof(long)<<"\t"<<sizeof(float)<<std::endl;
//    std::cout<<sizeof(Point3f)<<"\t"<<sizeof(Point2f)<<"\t"<<sizeof(Face)<<std::endl;
//    if (!infile.is_open())
//    {
//        std::cerr<<"Cannot find the model file: "<<file_name<<endl;
//        return false;
//    }
//    string id;
//    bool bFirst=true;
//    int nface=1;
//    list<Point3f> coord_list;
//    list<Point3f> normal_list;
//    list<Point2f> texture_list;
//    list<rawFace> face_list;
//    char temp_buf[512];
//    infile>>id;

//    std::chrono::time_point<std::chrono::system_clock> start, end;
//    std::chrono::duration<double> elapsed_seconds;
//    start = std::chrono::system_clock::now();
//    while(!infile.eof())
//    {
//        if (id=="v"){
//            coord_list.push_back(Point3f());
//            for (int i=0;i<3;i++)
//                infile>>coord_list.back()[i]  ;

//            //vmark.clear();
//        }else
//        if (id=="vn"){
//            normal_list.push_back(Point3f());
//            for (int i=0;i<3;i++){
//                infile>> normal_list.back()[i]  ;
//                //normal_list.back()[i]*=-1;
//            }
//            //vmark.clear();
//        }else
//        if (id=="vt"){
//            texture_list.push_back(Point2f());
//            for (int i=0;i<2;i++)
//                infile>>texture_list.back()[i]  ;
//            //vmark.clear();
//        }else
//        if (id=="f"){
//            if (bFirst){
//                string s;
//                infile>>s;
//                nface=0;
//                have_proterties[1]=have_proterties[2]=false;
//                have_proterties[0]=true;
//                for (int i=0;i<s.length()-1;i++)
//                    if (s[i]=='/')
//                    {
//                        have_proterties[++nface]=true;
//                        if (s[i+1]=='/'){
//                            have_proterties[nface]=false;
//                        }
//                    }
//                bFirst=false;
//                //std::cout<<infile.tellg()<<"\t"<<s.length()<<std::endl;
//                infile.seekg(int(infile.tellg())-s.length());
//            }

//            char c;
//            face_list.push_back(rawFace());
//            for (int i=0;i<face_dim;i++){
//                for (int j=0;j<3;j++){
//                    if (have_proterties[j]){
//                        infile>>face_list.back()[j*face_dim+i];
//                        --face_list.back()[j*face_dim+i];
//                    }
//                    if (j<2) infile>>c;
//                }
//            }
//       }else
//            infile.getline(temp_buf,512);
//        infile>>id;
//    }
//    end = std::chrono::system_clock::now();
//    elapsed_seconds = end-start;
//    std::cout<<"elapse time: "<<elapsed_seconds.count()<<std::endl;

//    std::cout<<id<<std::endl;
//    infile.close();

//    start = std::chrono::system_clock::now();
//    verts.clear();
//    texs.clear();
//    norms.clear();
//    faces.clear();
//    vector<Point3f> t_norms;
//    vector<Point2f> t_texs;

//    verts.reserve(coord_list.size());
//    t_norms.reserve(normal_list.size());
//    t_texs.reserve(texture_list.size());

//    for_each(coord_list.begin(),coord_list.end(),[this](const Point3f& it){this->verts.push_back(it);});
//    for_each(normal_list.begin(),normal_list.end(),[&t_norms](const Point3f& it){t_norms.push_back(it);});
//    for_each(texture_list.begin(),texture_list.end(),[&t_texs](const Point2f& it){t_texs.push_back(it);});

//    if (have_proterties[0])
//        faces.reserve(face_list.size());
//    if (have_proterties[1])
//        texs.resize(coord_list.size());
//    if (have_proterties[2])
//        norms.resize(coord_list.size());

//    for (auto fiter=face_list.begin(); fiter!=face_list.end();fiter++){
//        faces.push_back(Face(fiter->data()));
//        for (int i=0;i<face_dim;i++){
//            if (have_proterties[1])
//                texs[(*fiter)[i]]=t_texs[(*fiter)[i+face_dim]];
//            if (have_proterties[2])
//                norms[(*fiter)[i]]=t_norms[(*fiter)[i+(face_dim<<1)]];
//        }
//    }
//    face_properties_num=nface;
//    face_num=faces.size();
//    vert_num=verts.size();
//    tex_num=texs.size();
//    norm_num=norms.size();


//    end = std::chrono::system_clock::now();
//    elapsed_seconds = end-start;
//    std::cout<<"elapse time: "<<elapsed_seconds.count()<<std::endl;

//    return true;
//}

bool ObjModel::load(const std::string &file_name)
{
    using namespace std;
    FILE* infile;
    infile=fopen(file_name.c_str(),"rb");

    //std::cout<<sizeof(int)<<"\t"<<sizeof(long)<<"\t"<<sizeof(float)<<std::endl;
    std::cout<<sizeof(Point3f)<<"\t"<<sizeof(Point2f)<<"\t"<<sizeof(Face)<<std::endl;
    if (!infile)
    {
        std::cerr<<"Cannot find the model file: "<<file_name<<endl;
        return false;
    }
    char id[128];
    bool bFirst=true;
    int nface=1;
    list<Point3f> coord_list;
    list<Point3f> normal_list;
    list<Point2f> texture_list;
    list<rawFace> face_list;
    char temp_buf[512];

    fscanf(infile,"%s",id);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    start = std::chrono::system_clock::now();
    while(!feof(infile))
    {
        if (strncmp(id,"v",3)==0){
            coord_list.push_back(Point3f());
            for (int i=0;i<3;i++)
                fscanf(infile,"%f",&(coord_list.back()[i]))  ;

            //vmark.clear();
        }else
        if (strncmp(id,"vn",4)==0){
            normal_list.push_back(Point3f());
            for (int i=0;i<3;i++){
                 fscanf(infile,"%f",&(normal_list.back()[i]))  ;
                //normal_list.back()[i]*=-1;
            }
            //vmark.clear();
        }else
        if (strncmp(id,"vt",4)==0){
            texture_list.push_back(Point2f());
            for (int i=0;i<2;i++)
                 fscanf(infile,"%f",&(texture_list.back()[i]))  ;
            //vmark.clear();
        }else
        if (strncmp(id,"f",2)==0){
            if (bFirst){
                char s[128];
                fscanf(infile,"%s",s);
                nface=0;
                have_proterties[1]=have_proterties[2]=false;
                have_proterties[0]=true;
                for (int i=0;i<strlen(s)-1;i++)
                    if (s[i]=='/')
                    {
                        have_proterties[++nface]=true;
                        if (s[i+1]=='/'){
                            have_proterties[nface]=false;
                        }
                    }
                bFirst=false;
                //std::cout<<infile.tellg()<<"\t"<<s.length()<<std::endl;
                fseek(infile,ftell(infile)-strlen(s),SEEK_SET);
            }

            face_list.push_back(rawFace());
            for (int i=0;i<face_dim;i++){
                for (int j=0;j<3;j++){
                    if (have_proterties[j]){
                        fscanf(infile,"%d",&(face_list.back()[j*face_dim+i]));
                        --face_list.back()[j*face_dim+i];
                    }
                    if (j<2) fgetc(infile);
                }
            }
       }else
            fgets(temp_buf,512,infile);
        fscanf(infile,"%s",id);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    std::cout<<"elapse time: "<<elapsed_seconds.count()<<std::endl;

    std::cout<<id<<std::endl;
    fclose(infile);

    start = std::chrono::system_clock::now();
    verts.clear();
    texs.clear();
    norms.clear();
    faces.clear();
    vector<Point3f> t_norms;
    vector<Point2f> t_texs;

    verts.reserve(coord_list.size());
    t_norms.reserve(normal_list.size());
    t_texs.reserve(texture_list.size());

    for_each(coord_list.begin(),coord_list.end(),[this](const Point3f& it){this->verts.push_back(it);});
    for_each(normal_list.begin(),normal_list.end(),[&t_norms](const Point3f& it){t_norms.push_back(it);});
    for_each(texture_list.begin(),texture_list.end(),[&t_texs](const Point2f& it){t_texs.push_back(it);});

    if (have_proterties[0])
        faces.reserve(face_list.size());
    if (have_proterties[1])
        texs.resize(coord_list.size());
    if (have_proterties[2])
        norms.resize(coord_list.size());

    for (auto fiter=face_list.begin(); fiter!=face_list.end();fiter++){
        faces.push_back(Face(fiter->data()));
        for (int i=0;i<face_dim;i++){
            if (have_proterties[1])
                texs[(*fiter)[i]]=t_texs[(*fiter)[i+face_dim]];
            if (have_proterties[2])
                norms[(*fiter)[i]]=t_norms[(*fiter)[i+(face_dim<<1)]];
        }
    }
    face_properties_num=nface;
    face_num=faces.size();
    vert_num=verts.size();
    tex_num=texs.size();
    norm_num=norms.size();


    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    std::cout<<"elapse time: "<<elapsed_seconds.count()<<std::endl;

    return true;
}


bool ObjModel::save(const std::string &file_name)
{
    return false;
}


void Model::debug()
{
//    for_each(verts.begin(),verts.end(),[](const Point3f& it){
//        if (it.length()<2)  std::cout<<it<<std::endl; });
//    for_each(texs.begin(),texs.end(),[](const Point2f& it){ std::cout<<it<<std::endl; });
//    for_each(norms.begin(),norms.end(),[](const Point3f& it){    if (it.length()>2)  std::cout<<it<<std::endl; });
//    for_each(faces.begin(),faces.end(),[](const Face& it){ std::cout<<it<<std::endl; });

    std::cout<<face_num<<"\t"<<vert_num<<"\t"<<tex_num<<"\t"<<norm_num<<std::endl;
}
