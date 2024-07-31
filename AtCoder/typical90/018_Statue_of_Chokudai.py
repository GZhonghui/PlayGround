import math

def main():
    T=int(input())
    L,X,Y = [int(i) for i in input().split()]
    Q=int(input())

    def angle(p1,p2):
        h=abs(p1[2]-p2[2])
        def len2d(p1,p2):
            dx,dy=p1[0]-p2[0],p1[1]-p2[1]
            return math.sqrt(dx*dx+dy*dy)
        w=len2d(p1,p2)
        l=math.sqrt(h*h+w*w)
        return math.asin(h/l)*180/math.pi

    def solve(E):
        hl=0.5*L
        progress=-math.pi*2*E/T-0.5*math.pi
        p1=[X,Y,0]
        p2=[0,math.cos(progress)*hl,hl+math.sin(progress)*hl]
        return angle(p1,p2)

    for i in range(Q):
        E=int(input())
        print(solve(E%T))

if __name__=='__main__':
    main()