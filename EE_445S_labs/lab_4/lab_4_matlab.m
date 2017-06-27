clear all


% autocorrelation of pseudo random sequence
N = 18;
x = [1,-1,1,1,-1,1,-1,-1,-1,1,-1,1,1,-1,1,-1,-1,-1];
y = zeros(1,N);
for n=1:N
	temp = 0;
	for(i=1:N)
		ti = n+i;
		if(ti > N)
			ti = ti -N;
		end
		temp = temp+ x(i)*x(ti);
	end
	y(n) = temp;
end

y = (1/N)*y;
%stem(y);


%auto correlation on descramble output
x = [1,1,-1,-1,1,-1,1,1,1,-1];
N = 10
y = zeros(1,N);
for n=1:N
	temp = 0;
	for(i=1:N)
		ti = n+i;
		if(ti > N)
			ti = ti -N;
		end
		temp = temp+ x(i)*x(ti);
	end
	y(n) = temp;
end

y = (1/N)*y;
stem(y);
