//
// Created by Krisz on 17/07/2025.
//

#include "Object.h"

#include <cstdio>

Object::Object() {
    PosX = 800;
    PosY = 600;
    bLeft = false;
    bTowards = false;
    Speed = 5.f;
}

Object::~Object() {

}

void Object::Initialize() {
    std::printf("Position X: %f\nPosition Y: %f\n", PosX, PosY);
}

void Object::MoveLeft() {
    if (bLeft) {
        PosX -= Speed;
        printf("PosX: %f\n", PosX);
    } else {
        PosX += Speed;
        printf("PosX: %f\n", PosX);
    }
}

void Object::MoveTowards() {
    if (bTowards) {
        PosY -= Speed;
        printf("PosY: %f\n", PosY);
    } else {
        PosY += Speed;
        printf("PosY: %f\n", PosY);
    }
}

void Object::SetLeftDirection(bool bNewDirection) {
    bLeft = bNewDirection;
}

void Object::SetTowardsDirection(bool bNewDirection) {
    bTowards = bNewDirection;
}

