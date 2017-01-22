clear;
clc;

function[W, E]=neuro(L, in, X)
    
    rand('seed', getdate('s'));
    lc=length(L);
    ec=2;
    sc=size(X, 'r');
    a=0.2;
    
    I(1)=in+1;
    for l=2:1:lc
        I(l)=L(l-1)+1;
    end
    
    for l=1:1:lc
        for n=1:1:L(l)
            for i=1:1:I(l)
                W(l,n,i)=int(rand(1, 'uniform')*80)/100+0.1;
            end
        end
    end
    
    for e=1:1:ec
        
        E(e,:)=[e 0];
        
        for r=1:1:sc
        
        temp=I(1)-1;
        for n=1:1:L(1)
            S(1,n)=W(1,n,I(1));
            for i=1:1:temp
                S(1,n)=S(1,n)+W(1,n,i)*X(r,i);
            end
            Y(1,n)=(1/(1+exp(-S(1,n))));
        end
        
        for l=2:1:lc
            temp=l-1;
            temp2=I(l)-1;
            for n=1:1:L(l)
                S(l,n)=W(l,n,I(l));
                for i=1:1:temp2
                    S(l,n)=S(l,n)+W(l,n,i)*Y(temp,i);
                end
                Y(l,n)=(1/(1+exp(-S(l,n))));
            end
        end
        
        temp=I(1)-1;
        for n=1:1:L(lc)
            FP(lc,n)=Y(lc,n)*(1-Y(lc,n));
            temp2=X(r,temp+n)-Y(lc,n);
            E(e,2)=E(e,2)+temp2*temp2;
            D(lc,n)=temp2*FP(lc,n);
        end
        
        for l=lc-1:-1:1
            temp=l+1;
            SD=0;
            for n=1:1:L(temp)
                for i=1:1:I(temp)
                    SD=SD+D(temp,n)*W(temp,n, i);
                end
            end
            for n=1:1:L(l)
                FP(l,n)=Y(l,n)*(1-Y(l,n));
                D(l,n)=SD*FP(l,n);
            end
        end
        
        for l=lc:-1:2
            temp=l-1;
            temp2=I(l)-1;
            for n=1:1:L(l)
                for i=1:1:temp2
                    W(l,n,i)=W(l,n,i)+a*D(l,n)*Y(temp,i);
                end
                W(l,n,I(l))=W(l,n,I(l))+a*D(l,n);
            end
        end
        
        temp=I(1)-1;
        for n=1:1:L(1)
            for i=1:1:temp
                W(1,n,i)=W(1,n,i)+a*D(1,n)*X(r,i);
            end
            W(1,n,I(1))=W(1,n,I(1))+a*D(1,n);
        end
        
    end
    
    E(e,2)=sqrt(E(e,2)/(L(lc)*sc));
    
    end
    
endfunction

function[Y]=test(L, in, W, X)
    
    lc=length(L);
    tc=size(X, 'r');
    
    I(1)=in+1;
    for l=2:1:lc
        I(l)=L(l-1)+1;
    end
    
    for t=1:1:tc
    
        temp=I(1)-1;
        for n=1:1:L(1)
            S(1,n)=W(1,n,I(1));
            for i=1:1:temp
                S(1,n)=S(1,n)+W(1,n,i)*X(t,i);
            end
            A(1,n)=(1/(1+exp(-S(1,n))));
        end
        
        for l=2:1:lc
            temp=l-1;
            temp2=I(l)-1;
            for n=1:1:L(l)
                S(l,n)=W(l,n,I(l));
                for i=1:1:temp2
                    S(l,n)=S(l,n)+W(l,n,i)*A(temp,i);
                end
                A(l,n)=(1/(1+exp(-S(l,n))));
            end
        end
        
        Y(t,:)=A(lc,:);
    
    end;
    
endfunction

close;
close;

cd(get_absolute_file_path("irysy4x3.sce"));
f=read('iris.dat', 150, 4);
for i=1:1:50
    X(i,:)=[f(i,1:4) 1 0 0];
    t1=i+50;
    X(t1,:)=[f(t1,1:4) 0 1 0];
    t2=i+100;
    X(t2,:)=[f(t2,1:4) 0 0 1];
end

L=[4,3];
[W, E]=neuro(L, 4, X);
T=test(L, 4, W, X);

plot(E(:,1), E(:,2), 'r');
g2=gca();
xlabel(g2, 'liczba epok');
ylabel(g2, 'błąd na wyjściu sieci');

scf;
g1=gca();
xlabel(g1, 'długość kielicha');
ylabel(g1, 'szerokość kielicha');
v1=1;
v2=2;
tc=size(X, 'r');
for i=1:1:tc
    if T(i,1)>T(i,2)
        if T(i,1)>T(i,3)
            plot(X(i, v1), X(i, v2) ,'r*:');
        else
            plot(X(i, v1), X(i, v2) ,'bO:');
        end
    else
        if T(i,2)>T(i,3)
            plot(X(i, v1), X(i, v2) ,'g+:');
        else
            plot(X(i, v1), X(i, v2) ,'bO:');
        end
    end
end
