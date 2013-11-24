#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <cstring>
template <class T,int size>
struct LightVector
{
 public:
    LightVector(){
        //memset(v,0,size*sizeof(T));
    }
    LightVector(const T* vl){
        memcpy(v,vl,size*sizeof(T));
    }

    inline LightVector& operator=(const LightVector& p3){
        memcpy(v,p3.v,size*sizeof(T));
        return *this;
    }

    inline LightVector& operator=(const T* vl){
        memcpy(v,vl,size*sizeof(T));
        return *this;
    }

    inline T& operator[](int n) {
        return v[n];
    }
    inline const T& operator[](int n) const {
        return v[n];
    }
    inline T& at(int n){
        return v[n%size];
    }
    inline const T& at(int n) const {
        return v[n%size];
    }
    inline const T* data(){
        return v;
    }

    //friend std::ostream& operator<<(std::ostream&,const LightVector<T,size>&);
 private:
        T v[size];
};
template<class T, int size>
std::ostream& operator<<(std::ostream& o, const LightVector<T,size>& lv){
    for (int i=0;i<size-1;i++)
        o<<lv[i]<<"\t";
    o<<lv[size-1];
    return o;
}

class Model
{
public:
    Model();
	virtual ~Model();
public:
    enum {CoordID=0,TextureID,NormalID};
    enum {Triangle=3,Quad};
    typedef LightVector<float,3> Point3f;
    typedef LightVector<float,2> Point2f;
    typedef LightVector<unsigned long,4*3> rawFace4d;
    typedef LightVector<unsigned long,3*3> rawFace3d;
    typedef rawFace3d rawFace;

    typedef LightVector<unsigned long,4> Face4d;
    typedef LightVector<unsigned long,3> Face3d;
    typedef Face3d Face;

public:
    virtual bool rawload(const std::string& file_name)=0;
    virtual bool save(const std::string& file_name)=0;
    virtual bool load(const std::string& file_name)=0;
    virtual void debug();

public:
    std::vector<Point3f> verts;
    std::vector<Point2f> texs;
    std::vector<Point3f> norms;
    //std::vector<Face4d> faces;
    std::vector<Face> faces;
    std::vector<rawFace> rawfaces;
    bool have_proterties[3];
    int face_dim;
    int face_num;
    int vert_num;
    int tex_num;
    int norm_num;
    int face_properties_num;
};

class ObjModel:public Model
{
public:
    ObjModel();

public:
    bool rawload(const std::string& file_name);
    bool load(const std::string& file_name);
    bool save(const std::string& file_name);

};


#endif // MODEL_H
