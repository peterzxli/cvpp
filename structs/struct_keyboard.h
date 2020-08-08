#ifndef KEYBOARD_H
#define KEYBOARD_H

namespace cvpp
{

class Keyboard
{

protected:

public:

    bool up,down,left,right;
    bool q,w,e,a,s,d,z,x,c;
    bool i,o,p,j,k,l,b,n,m;
    bool r,t,y,u,f,g,h,v;

    bool kp0,kp1,kp2,kp3,kp4,kp5,kp6,kp7,kp8,kp9;

    bool lalt,lctrl,lshift,ralt,rctrl,rshift;
    bool enter,space,tab;

public:

    Keyboard()
    {
        up = down = left = right = false;
        q = w = e = a = s = d = z = x = c = false;
        i = o = p = j = k = l = b = n = m = false;
        r = t = y = u = f = g = h = v = false;
        lalt = lctrl = lshift = ralt = rctrl = rshift = false;
        enter = space = tab = false;

        kp1 = kp2 = kp3 = kp4 = kp5 = kp6 = kp7 = kp8 = kp9 = false;
    }

    const bool udlr() const { return up || down || left || right ; }

};

}

#endif

