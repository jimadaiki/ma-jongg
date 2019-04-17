#include <stdio.h>
#include <string.h>

int flag_place; //本場が増えるかどうか
int place = 0; //場数
int kyotaku = 0; //供託

struct players
{	
	char name[20]; //名前
	int point ; //持ち点
	char h[4]; //自風
	int reach; //リーチをしていたか
	int count_r; //リーチ回数
	int count_t; //テンパイ回数
	int count_w; //上がり回数
	int avr; //平均打点
};




//-1は禁止入力
int point_parent[13][11] = { //親の点数表
		{-1,-1,1500,2000,2400,2900,3400,3900,4400,4800,5300} ,
		{2100,2400,2900,3900,4800,5800,6800,7700,8700,9600,10360},
		{3900,4800,5800,7700,9600,12000,12000,12000,12000,12000,12000},
		{7800,9600,12000,12000,12000,12000,12000,12000,12000,12000,12000},
		{12000,12000,12000,12000,12000,12000,12000,12000,12000,12000,12000},
		{18000,18000,18000,18000,18000,18000,18000,18000,18000,18000,18000},
		{18000,18000,18000,18000,18000,18000,18000,18000,18000,18000,18000},
		{24000,24000,24000,24000,24000,24000,24000,24000,24000,24000},
		{24000,24000,24000,24000,24000,24000,24000,24000,24000,24000},
		{24000,24000,24000,24000,24000,24000,24000,24000,24000,24000},
		{36000,36000,36000,36000,36000,36000,36000,36000,36000,36000},
		{36000,36000,36000,36000,36000,36000,36000,36000,36000,36000},
		{48000,48000,48000,48000,48000,48000}
};

int point_child[13][11] = { //子の点数表
		{-1,-1,1000,1300,1600,2000,2300,2600,2900,3200,3600},
		{1500,1600,2000,2600,3200,3900,4500,5200,5800,6400,7100},
		{2700,3200,3900,5200,6400,8000,8000,8000,8000,8000,8000},
		{5200,6400,8000,8000,8000,8000,8000,8000,8000,8000,8000},
		{8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000},
		{12000,12000,12000,12000,12000,12000,12000,12000,12000,12000},
		{12000,12000,12000,12000,12000,12000,12000,12000,12000,12000},
		{16000,16000,16000,16000,16000,16000,16000,16000,16000,16000},
		{16000,16000,16000,16000,16000,16000,16000,16000,16000,16000},
		{16000,16000,16000,16000,16000,16000,16000,16000,16000,16000},
		{24000,24000,24000,24000,24000,24000,24000,24000,24000,24000},
		{24000,24000,24000,24000,24000,24000,24000,24000,24000,24000},
		{32000,32000,32000,32000,32000,32000,32000,32000,32000,32000}
};

int givepoint_parent[13][11] = { //親にツモられた時
	{-1,-1,500,700,800,1000,1200,1300,1500,1600,1800},
	{700,-1,1000,1300,1600,2000,2300,2600,2900,3200,3600},
	{1300,1600,2000,2600,3200,4000,4000,4000,4000,4000,4000},
	{2600,3200,4000,4000,4000,4000,4000,4000,4000,4000,4000},
	{4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000},
	{6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000},
	{6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000},
	{8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000},
	{8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000},
	{8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000},
	{12000,12000,12000,12000,12000,12000,12000,12000,12000,12000},
	{12000,12000,12000,12000,12000,12000,12000,12000,12000,12000},
	{16000,16000,16000,16000,16000,16000,16000,16000,16000,16000},
};

int givepoint_child[13][11] = { //子にツモられたとき
	{-1,-1,300,400,400,500,600,700,800,800,900},
	{400,-1,500,700,800,1000,1200,1300,1500,1600,1800},
	{700,800,1000,1300,1600,2000,2000,2000,2000,2000,2000},
	{1300,1600,2000,2000,2000,2000,2000,2000,2000,2000,2000},
	{2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000},
	{3000,3000,3000,3000,3000,3000,3000,3000,3000,3000,3000},
	{3000,3000,3000,3000,3000,3000,3000,3000,3000,3000,3000},
	{4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000},
	{4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000},
	{6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000},
	{6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000},
	{6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000},
	{8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000},
};



void print( struct players player[], int f, int d ) //点数等表示
{	
	if(f == 1){ //東場なら
		printf("<--東%d局%d本場 供託%d点-->\n",d ,place, kyotaku);
	}else{
		printf("<--南%d局%d本場 供託%d点-->\n",d, place, kyotaku );
	}
	printf("%s家:%s %d点\n", player[0].h,player[0].name,player[0].point );
	printf("%s家:%s %d点\n", player[1].h,player[1].name,player[1].point );
	printf("%s家:%s %d点\n", player[2].h,player[2].name,player[2].point );
	printf("%s家:%s %d点\n", player[3].h,player[3].name,player[3].point );

	return;
}

int  end( int d , struct players player[] ) //局終わりアクション
{

	int han,hu; //飜数と符数
	int i;
	int t[4] = {0};
	int count = 0; //テンパイ人数
	int who; //上がった人
	int who_ron; //振り込んだ人
	int flag; //親が流れるか否か
	

	flag_place = 0; //初期化

	printf("<--リーチした人はいましたか?(リーチ:1 ノーリーチ:0)-->\n");
	for( i = 0; i < 4; i++ ){	//リー棒計算
		printf("%s:", player[i].name);
		scanf("%d",&player[i].reach);
		if( player[i].reach == 1) {
			player[i].count_r++;	//リーチ回数カウント
			player[i].point = player[i].point - 1000;
			kyotaku = kyotaku + 1000;
		}
	}

	if( d == 1 ){ //ロン

		printf("<--誰が上がりましたか？-->\n");
		printf("1:%s 2:%s 3:%s 4:%s\n",player[0].name, player[1].name, player[2].name, player[3].name );
		do{
			scanf("%d",&who);
		}while( who > 4 );

		who = who - 1;

		player[who].count_w++; //上がった回数をプラス1する
		

		printf("<--飜数と符数を入力してください-->\n");
		printf("飜数:");
		scanf("%d",&han);
		if( han <= 4 ){ //4飜以下なら符数も入力
			printf("符数:");
			scanf("%d",&hu);
		}else{	//5飜以上は変わらないので適当に代入
			hu = 40;	
		}
		
		if( who == 0 ) {
			flag = 1; //親が上がったら
		}

		printf("<--誰から上がりましたか？-->\n");

		for(int i = 0; i < 4; i++ ){ 
			if( i != who ){
		    	printf("%d:%s\n", i + 1 , player[i].name);
			}
		}

		scanf("%d",&who_ron); //放銃者

		who_ron--; //配列の添字に対応させるため

		int hu2; //符を配列の添字に変換

		for( i = 3; i < 12; i++ ){ //変換
			if( hu == i * 10 ) hu2 = i - 1;
		}

		//点数計算

		if( who == 0 ){ //上がったのが親なら
			player[who].avr += point_parent[han-1][hu2]; //単純打点
			player[who].point = player[who].point + ( point_parent[han-1][hu2] + place * 300 + kyotaku );
			player[who_ron].point = player[who_ron].point - ( point_parent[han-1][hu2] + place * 300 ) ;
			flag = 1;
			place++;
		}else{			//上がったのが子なら
			player[who].avr += point_child[han-1][hu2]; //単純打点
			player[who].point = player[who].point + ( point_child[han-1][hu2] + place * 300 + kyotaku );
			player[who_ron].point = player[who_ron].point - ( point_child[han-1][hu2] + place * 300 );
			printf("%d飜%d符 %d点\n",han-1,hu2, point_child[han-1][hu2] );
			printf("%s:%d\n",player[who].name,player[who].point );
			flag = 0;
			place = 0;
		}

		kyotaku = 0;

		return flag;
		

	}else if( d == 2 ){ //ツモ
		printf("<--誰が上がりましたか？-->\n");
		printf("1:%s 2:%s 3:%s 4:%s\n",player[0].name, player[1].name, player[2].name, player[3].name );
		scanf("%d",&who);

		who = who - 1;

		player[who].count_w++; //上がった回数をプラス1する

		printf("<--飜数と符数を入力してください-->\n");
		printf("飜数:");
		scanf("%d",&han);
		if( han <= 4 ){ //4飜以下なら符数も入力
			printf("符数:");
			scanf("%d",&hu);
		}else{	//5飜以上は変わらないので適当に代入
			hu = 40;	
		}

		int hu2; //符を配列の添字に変換

		if( hu == 20 ) hu2 = 0;
		if( hu == 25 ) hu2 = 1;

		for( i = 3; i < 12; i++ ){ //変換
			if( hu == i * 10 ) hu2 = i - 1;
		}
		
		

		if( who == 0 ) { //親が上がったら
			player[who].avr += point_parent[han-1][hu2];
			player[who].point = player[who].point + ( point_parent[han-1][hu2] + place * 300 + kyotaku );
			flag = 1; //親継続フラグ
			for( i = 1; i < 4; i++ ){ //親以外
				player[i].point = player[i].point - ( ( givepoint_parent[han-1][hu2] ) + ( place * 100 ) );
			}
			place++;
		}else{ //子が上がったら

			flag = 0; //親流れ

			int p_child,p_parent; //子が払う点数と親が払う点数

			p_child = givepoint_child[han-1][hu2] ;

			if( ( ( han == 2 || han == 3) && hu == 20 ) || ( han == 1 && hu == 30 ) || ( ( han == 1 || han == 2 ) && hu == 40 ) || 
							( han == 2 && hu == 70 ) || ( han == 1 && hu == 80) || ( ( han == 1 || han == 2 ) && hu == 90 ) ) { //親の点数分加算
				p_parent = givepoint_child[han-1][hu2] * 2 - 100 ;
			}else{
				p_parent = givepoint_child[han-1][hu2] * 2;
			}

			//上がった人の点数加算
			player[who].avr += p_child * 2 + p_parent;
			player[who].point = player[who].point + ( p_child * 2 + p_parent + place * 300 + kyotaku );

			for( i = 0; i < 4; i++ ){
				if( who != i ){ 
					if( i == 0 ){ //親の点数計算
						player[i].point = player[i].point - ( p_parent + place * 100 );
					}else{ //子の点数計算
						player[i].point = player[i].point - ( p_child + place * 100 );
					}
				}
			}
			place = 0;
		}

		
		kyotaku = 0;

		return flag;

	}else{ //流局
		printf("<--ノーテン:0 テンパイ:1-->\n");
		place++;
		for( i = 0; i < 4; i++ ){	//テンパイ判断
			printf("%d:%s",i+1, player[i].name);
			scanf("%d",&t[i]);
			if( t[i] == 1 ) count++;		
		}


		printf("count = %d\n",count );
		
		if( count == 1 ){ //1人テンパイ
			for( i = 0; i < 4; i++ ){
				if( t[i] == 1 ){
					if( i == 0 ){ //親なら
						flag = 1; //親継続フラグ
						//flag_place = 1; //本場を増やすフラグ
					}else{
						flag = 0; //親流れ
						//printf("aaaaaaa\n");
					}
					player[i].point += 3000;
					player[i].count_t++;
					
				}else{
					player[i].point -= 1000;
				}
			}
		}else if( count == 2 ){ //2人テンパイ
			for( i = 0; i < 4; i++ ){
				if( t[i] == 1 ){
					if( i == 0 ){ //親なら
						flag = 1; //親継続フラグ
						//flag_place = 1; //本場を増やすフラグ
					}else if( t[0] != 1 ){
						flag = 0;
					}
					player[i].point += 1500;
					player[i].count_t++;
				}else{
					player[i].point -= 1500;
				}
			}
		}else if( count == 3 ){ //3人テンパイ
			for( i = 0; i < 4; i++ ){
				if( t[i] == 1 ){
					if( i == 0 ){ //親なら
						flag = 1; //親継続フラグ
						//flag_place = 1; //本場を増やすフラグ
					}else if( t[0] != 1 ){
						flag = 0;
					}
					player[i].point += 1000;
					player[i].count_t ++;
				}else{
					player[i].point -= 3000;
				}
			}
		}else{	//全員ノーテン
			flag = 0;
			//flag_place = 1; //本場を増やすフラグ
		}
	}

	return flag;
}


int main (void)
{

	int field; //東場:1 南場:2
	int station; //局数


	struct players player[4];
	struct players dammy_player[4];

	FILE *fp;
	fp = fopen( "example.csv", "w" );
	if( fp == NULL ){
		printf("ファイルエラー\n");
	}else{


		fprintf( fp, "プレイヤー,最終点数\n");

		int cont; //続けるか続けないか

		do{

			for( int i = 0; i < 4; i++ ){  //プレイヤー情報初期化
				player[i].point = 25000;
				player[i].count_t = 0;
				player[i].count_r = 0;
				player[i].count_w = 0;
				player[i].avr =  0;
			}

			strcpy(player[0].h, "東");
			strcpy(player[1].h, "南");
			strcpy(player[2].h, "西");
			strcpy(player[3].h, "北");

		    int rule; //飛びあり、なし

			/*printf("飛びあり:1, なし:0\n");
			scanf("%d",&rule);*/

			printf("プレイヤーの名前を入力してください\n");
			printf("東家:");
			scanf("%s",player[0].name);
			printf("南家:");
			scanf("%s",player[1].name);
			printf("西家:");
			scanf("%s",player[2].name);
			printf("北家:");
			scanf("%s",player[3].name);

			int dec; //上がったか流局か
			int who; //誰が上がったか
			int flag_parent; //親が流れるか否か

			int i,j;
			int max = -1;
			int max_player; //流局時1位の人


			for( field = 1; field <= 2 ; field++ ){ //東:1 南:2
				for( station = 1;  station <= 4; station++ ){ //局数
					
						print( player, field, station );
						printf("1:ロン 2:ツモ 3:流局\n");
						scanf("%d",&dec);

						if( field == 2 && station == 4 && dec == 3 ){ //最終局に流局してしまった場合、供託はトップどり
							for( i  = 0; i < 4; i++ ){
									if( max < player[i].point ){
										max = player[i].point;
										max_player = i;
									}
							}
							player[max_player].point += kyotaku;

						}

						flag_parent = end( dec , player ); //局終わりのアクション
						
						if( flag_parent == 1) {
							station = station - 1; //親連チャン
						}else{ //構造体コピー
							memcpy(&dammy_player[2], &player[2], sizeof(player[2]) );
							memcpy(&player[2], &player[3], sizeof(player[3]) );
							memcpy(&dammy_player[1], &player[1], sizeof(player[1]) );
							memcpy(&player[1], &dammy_player[2], sizeof(dammy_player[2]) );
							memcpy(&dammy_player[0], &player[0], sizeof(player[0]) );
							memcpy(&player[0], &dammy_player[1], sizeof(dammy_player[1]) );
							memcpy(&player[3], &dammy_player[0], sizeof(dammy_player[0]) );
							for( i = 0; i < 4; i++ ){ //方角変え
								if( i == 0 ) strcpy( player[i].h, "東" );
								else if( i == 1 ) strcpy( player[i].h , "南");
								else if( i == 2 ) strcpy( player[i].h , "西");
								else strcpy( player[i].h, "北" );
							}

						}
					
					
					//printf("station = %d\n", station);
				}
				
			}

			struct  players tmp;

			//降順にソート
			for( i = 0 ;i < 4; i++ ){
				for( j = i + 1; j < 4; j++ ){
					if( player[i].point < player[j].point ){
						memcpy( &tmp,&player[i],sizeof(player[i]) );
						memcpy( &player[i],&player[j],sizeof(player[j]) );
						memcpy( &player[j],&tmp,sizeof(tmp) );
					}
				}
			}

			//player[0].point += a; //供託があったらプラス



			for( i = 0; i < 4; i++ ){
				printf("%d位:%s %d点 リーチ回数:%d回 テンパイ回数:%d回 上がり回数:%d回\n",i+1, player[i].name, player[i].point ,player[i].count_r, player[i].count_t, player[i].count_r );
				fprintf( fp,"%s, %d\n" , player[i].name, player[i].point);
			}

			printf("続ける:1 やめる:0\n");
			scanf("%d",&cont);
			
		}while( cont == 1 );
	}

	fclose(fp);

	return 0;
} 