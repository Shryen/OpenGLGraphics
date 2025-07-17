#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
    Object();
    ~Object();

    void Initialize();

    void MoveLeft();
    void MoveTowards();

    void SetLeftDirection(bool bNewDirection);
    void SetTowardsDirection(bool bNewDirection);
private:
    float PosX, PosY;

    bool bLeft;
    bool bTowards;
    float Speed;
};



#endif //OBJECT_H
