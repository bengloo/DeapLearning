format("v",10);
nbdata=9
//NBDATA=2
n0=2//nbentre(0)
n1=1//nbentre(1)=nbneurone(0)
n2=1//nbentre(2)=nbneurone(1)
a=0.1 //learning rate

X = [0 1/3 2/3 0 1/3 2/3 0 1/3 2/3;0 0 0 1/3 1/3 1/3 2/3 2/3 2/3];X=matrix(X, n0, nbdata)

//initialisation
    //c0 N0
        A0 = [0 0 0 0 0 0 0 0 0];A0=matrix(A0, n1, nbdata)
        dz0 = [0 0 0 0 0 0 0 0 0];dz0=matrix(dz0, n1, nbdata)
        w0 = [0; 1/2];w0=matrix(w0, n1, n0)
        dw0 = [0 0];dw0=matrix(dw0, n1, n0)
        b0 = [1];b0=matrix(b0,n1,1)
        db0 = [0];db0=matrix(db0,n1,1)
    //C1 N0
        A1 = [0 0 0 0 0 0 0 0 0];A1=matrix(A1,n2,nbdata)
        dz1 = [0 0 0 0 0 0 0 0 0];dz1=matrix(dz1,n2,nbdata)
        w1 = [0];w1=matrix(w1,n2,n1)
        dw1 = [0];dw1=matrix(dw1,n2,n1)
        b1 = [1];b0=matrix(b0,n2,1)
        db1 = [0];db1=matrix(db1,n2,1)   
    Y = [0 0 0 1 0 0 1 1 0];matrix(Y, 1, nbdata)
//iteration 0
    //forward_propagation
        A0=1./(1+exp(-(w0*X+b0)))
        A1=1./(1+exp(-(w1*A0+b0)))
    //back_propagation
        dz1=A1-Y
        dw1=(1/nbdata).*dz1*(A0')
        db1=(1/nbdata).*sum(dz1)
        
/*        dz0=(w1')*dz1.*(A0.*(1-A0))
        dw0=(1/nbdata).*dz0*(X')
        db0=(1/nbdata).*sum(dz0)    
    //update
        w0=w0-a*dw0
        b0=b0-a*db0
        w1=w1-a*dw1
        b1=b1-a*db1
//iteration 1
    //forward_propagation
        A0=1./(1+exp(-(w0*X+b0)))
        A1=1./(1+exp(-(w1*A0+b0)))
    //back_propagation
        dz1=A1-Y
        dw1=(1/nbdata).*dz1*(A0')
        db1=(1/nbdata).*sum(dz1)
        
        dz0=(w1')*dz1.*(A0.*(1-A0))
        dw0=(1/nbdata).*dz0*(X')
        db0=(1/nbdata).*sum(dz0)    
    //update
        w0=w0-a*dw0
        b0=b0-a*db0
        w1=w1-a*dw1
        b1=b1-a*db1
//iteration 2
    //forward_propagation
        A0=1./(1+exp(-(w0*X+b0)))
        A1=1./(1+exp(-(w1*A0+b0)))
    //back_propagation
        dz1=A1-Y
        dw1=(1/nbdata).*dz1*(A0')
        db1=(1/nbdata).*sum(dz1)
        
        dz0=(w1')*dz1.*(A0.*(1-A0))
        dw0=(1/nbdata).*dz0*(X')
        db0=(1/nbdata).*sum(dz0)    
    //update
        w0=w0-a*dw0
        b0=b0-a*db0
        w1=w1-a*dw1
        b1=b1-a*db1
*/







