format("v",9);
//nbdata=3*3
nbdata=10*10;
//NBCOUCHE=2
n0=2;//nbentre(0)
n1=1;//nbentre(1)=nbneurone(0)
n2=1;//nbentre(2)=nbneurone(1)
a=0.1; //learning rate


//dataset
//X = [0 1/3 2/3 0 1/3 2/3 0 1/3 2/3;0 0 0 1/3 1/3 1/3 2/3 2/3 2/3];X=matrix(X, n0, nbdata);
//X = [0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9;0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.3 0.3 0.3 0.3 0.3 0.3 0.3 0.3 0.3 0.3 0.4 0.4 0.4 0.4 0.4 0.4 0.4 0.4 0.4 0.4 0.5 0.5 0.5 0.5 0.5 0.5 0.5 0.5 0.5 0.5 0.6 0.6 0.6 0.6 0.6 0.6 0.6 0.6 0.6 0.6 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.8 0.8 0.8 0.8 0.8 0.8 0.8 0.8 0.8 0.8 0.9 0.9 0.9 0.9 0.9 0.9 0.9 0.9 0.9 0.9];X=matrix(X, n0, nbdata);

X = [0.599690 0.414375 0.398864 0.427769 0.448516 0.706707 0.966040 0.654532 0.610347 0.172413 0.177815 0.079034 0.153640 0.823051 0.146017 0.486061 0.391670 0.623899 0.240601 0.009767 0.923440 0.945885 0.822118 0.566080 0.142452 0.840618 0.749050 0.488773 0.531297 0.639674 0.700375 0.423020 0.026171 0.882580 0.098587 0.955889 0.608820 0.911507 0.502190 0.863403 0.216080 0.964910 0.623674 0.867819 0.765506 0.832284 0.633227 0.557926 0.302223 0.926170 0.332853 0.422837 0.783832 0.372612 0.811930 0.930665 0.940037 0.993140 0.349257 0.718681 0.368451 0.580643 0.806268 0.661077 0.579076 0.509301 0.469306 0.853603 0.266481 0.539161 0.462230 0.106421 0.365400 0.965977 0.960520 0.829419 0.235623 0.330649 0.548631 0.150383 0.578973 0.039637 0.591822 0.301418 0.119455 0.936715 0.310405 0.983951 0.142697 0.390461 0.634587 0.432187 0.629942 0.912101 0.754562 0.306281 0.722168 0.381815 0.239158 0.172293;0.003119 0.878193 0.340164 0.219232 0.871772 0.256768 0.105645 0.676600 0.542035 0.408153 0.010556 0.168505 0.611645 0.736984 0.388552 0.745707 0.900437 0.790535 0.051668 0.689117 0.716473 0.889480 0.600417 0.432465 0.738494 0.320268 0.919652 0.902689 0.311823 0.677313 0.125735 0.092046 0.046919 0.266772 0.892347 0.022027 0.901773 0.430938 0.477587 0.644642 0.704022 0.965130 0.453682 0.154971 0.507492 0.465881 0.255304 0.659399 0.440507 0.400810 0.882059 0.941674 0.334343 0.286022 0.236015 0.028010 0.895574 0.563711 0.860959 0.114762 0.550965 0.001678 0.138569 0.108491 0.587247 0.911929 0.932138 0.253139 0.226215 0.078411 0.469826 0.402267 0.099561 0.714657 0.684658 0.328971 0.410062 0.041892 0.991726 0.127707 0.659684 0.048280 0.893240 0.858303 0.840580 0.581685 0.043136 0.675805 0.949928 0.103216 0.219880 0.870210 0.762836 0.178574 0.062484 0.333535 0.345918 0.313990 0.683234 0.358613];X=matrix(X, n0, nbdata);

//Y = [0 0 0 1 0 0 1 1 0];matrix(Y, 1, nbdata);
//Y = [0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1 1 1 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0 0 0 1 1 1 1 1 0 0 0 0 0 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 0 0 0 1 1 1 1 1 1 1 1 0 0 1 1 1 1 1 1 1 1 1 0];matrix(Y, 1, nbdata);

Y = [0 1 0 0 1 0 0 1 0 1 0 1 1 0 1 1 1 1 0 1 0 0 0 0 1 0 1 1 0 1 0 0 1 0 1 0 1 0 0 0 1 1 0 0 0 0 0 1 1 0 1 1 0 0 0 0 0 0 1 0 1 0 0 0 1 1 1 0 0 0 1 1 0 0 0 0 1 0 1 0 1 1 1 1 1 0 0 0 1 0 0 1 1 0 0 1 0 0 1 1];matrix(Y, 1, nbdata);


//initialisation
    //c0 N0
        A0= zeros(n1, nbdata);
        dz0 = zeros(n1, nbdata);
        w0 = [0; 1/2];w0=matrix(w0, n1, n0);
        dw0 = [0 0];dw0=matrix(dw0, n1, n0);
        b0 = [1];b0=matrix(b0,n1,1);
        db0 = [0];db0=matrix(db0,n1,1);
    //C1 N0
        A1 = zeros(n2,nbdata);
        dz1 = zeros(n2,nbdata);
        w1 = [0];w1=matrix(w1,n2,n1);
        dw1 = [0];dw1=matrix(dw1,n2,n1);
        b1 = [1];b0=matrix(b0,n2,1);
        db1 = [0];db1=matrix(db1,n2,1);
    
   
    
for(i=0:(10000));
    disp("iteration:",i);
    //forward_propagation
        A0=1./(1+exp(-(w0*X+b0)));
        A1=1./(1+exp(-(w1*A0+b1)));
    //back_propagation
        dz1=A1-Y;
        dw1=(1/nbdata).*dz1*(A0');
        db1=(1/nbdata).*sum(dz1);
        
        dz0=(w1')*dz1.*(A0.*(1-A0));
        dw0=(1/nbdata).*dz0*(X');
        db0=(1/nbdata).*sum(dz0);    
    //update
        w0=w0-a*dw0
        b0=b0-a*db0
        w1=w1-a*dw1
        b1=b1-a*db1
    //accurenci score
        res=0;
        for(j=1:(nbdata));
            if((A1(1,j)>1/2&&Y==1)||(A1(1,j)<=1/2&&Y==0)) then 
                res= res+1
            end;
        end; 
        res
end;






