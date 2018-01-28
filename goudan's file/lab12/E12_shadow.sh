

BEGIN {

}

{
	table[NR]=$0;
}

END {
	k = 0
	name[1]=1
	for(i = 1;i <= NR;i=i+1) {
		indexs=split(table[i],array," ");
		for(j=2;j<=indexs;j=j+1) {
			if(array[j]!="01NYHOV") {
				k=k+1
				name[k] = array[j];
			}
			else
				break;
		}
	}
	srand();
	for(i =1;i<=NR;i=i+1) {
                indexs = split(table[i],array," ");
		studentnumber=0
		while(studentnumber < 100000) {
			studentnumber = int(rand() * 1000000)
		}
		printf studentnumber" "
		sign = 0
                for(j = 2; j <= indexs ; j=j+1) {
                        if(array[j] != "01NYHOV" && sign == 0) {
				number = int(rand()*10000 % (k) + 1);
				printf name[number]" "
				name[number]=name[k];
				k=k-1;
			}else {
				sign = 1; 
				printf array[j]" ";
                        }        
                }
		printf "\n"
        }
}
