#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>//����ļ���Ϣ


#define MAX_LINE_LENGTH 250
FILE* infile = NULL;
FILE* outfile = NULL;
char sbuf[MAX_LINE_LENGTH+1];
char* ch;


/****************�ļ�����****************/

void handle_c_comment(void) {
    while(1) {
        if(*ch == '\0'){
            if(fgets(sbuf, MAX_LINE_LENGTH, infile) == NULL){
                fprintf(stderr, "���ļ���ע�Ϳ��������⣬û����Ե� /* */\n");
                exit(1);
            }
            ch = sbuf;
        }
        while(*ch != '/' && *ch != '\0'){
            fputc(*ch, outfile);
            ++ch;
        }
        if(*ch == '\0') continue;
        else{
            fputc('/',outfile);
            if(*(ch-1) == '*'){
                ++ch;
                break;
            }else{
                ++ch;
            }
        }
    }
}


void handle_cpp_comment(void) {
    fputc('*',outfile);     //ǰ��ɲ��üӿո�
    //fputs("* ",outfile);    //�Ӹ��ո�
    ++ch;
    while(1){
        if( *ch == '\0'){
            if(fgets(sbuf, MAX_LINE_LENGTH, infile) == NULL){
                fputs("*/",outfile);
                exit(0);
            }else {
                ch = sbuf;
            }
        }
        while(*ch != '\n' && *ch != '\0' && *ch != '/'){
            fputc(*ch,outfile);
            ++ch;
        }
        if(*ch == '\n'){
            fputs(" */\n",outfile); //�Ӹ��ո�
            ++ch;
            break;
        }else if (*ch == '/'){
            if(*(ch-1) == '*' ){
                fputs(" /",outfile);
            }else{
                fputc('/', outfile);
            }
            ++ch;
        }
    }
}

void handle_string(void) {
    fputc('\"', outfile);
    ++ch;
    while(1){
        if(*ch == '\0'){
            if(fgets(sbuf, MAX_LINE_LENGTH, infile) == NULL) {
                fprintf(stderr, "Error: Probably syntax error becase reach EOF before the end of string\n");
                exit(2);
            }
            ch = sbuf;
        }
        while(*ch != '\"' && *ch != '\0') {
                fputc(*ch, outfile);
                ++ch;
        }
        if(*ch == '\0') continue;
        else if(*ch == '\"') {
            fputc('\"', outfile);
            ++ch;
            break;
        }
    }
}

void process_file(char *file_source_path, char *file_destination_path){
    infile  = fopen(file_source_path, "r");
    outfile = fopen(file_destination_path, "w");
    while(fgets(sbuf,MAX_LINE_LENGTH,infile)){
        ch = sbuf;
        while(*ch != '\0') {
            switch(*ch){
                case '/':
                    fputc(*ch, outfile);
                    ++ch;
                    if(*ch == '*') {
                        handle_c_comment(); // ���� /* */�е�//
                    } else if (*ch == '/'){
                        // ��ӡҪ�������
                        //puts(sbuf);
                        printf("%s", sbuf);
                        handle_cpp_comment();
                    } else {
                        fputc(*ch,outfile);
                        ++ch;
                    }
                    break;
                case '\"':
                    handle_string();    //���� "" �е�//
                    break;
                default:
                    fputc(*ch,outfile);
                    ++ch;
                    break;
            }
        }
    }
    return;
}


/*****************Ŀ¼����******************/


char* str_contact(char* str1,char* str2){//�ַ�������
	char* result;
	result=(char*)malloc(strlen(str1)+strlen(str2)+1);//str1�ĳ���+str2�ĳ���+\0;
	if(!result){//����ڴ涯̬����ʧ��
		printf("malloc error\n");
		exit(1);
	}
	strcat(result,str1);
	strcat(result,str2);//�ַ���ƴ��
	return result;
}

int is_dir(char* path){//�ж��Ƿ���Ŀ¼
	struct stat st;
	stat(path,&st);
	if(S_ISDIR(st.st_mode)){
		return 1;
	}
	else{
		return 0;
	}
}

/*�ַ���������*/
int endwith(char* s,char c){//�����ж��ַ�����β�Ƿ�Ϊ��/��
	if(s[strlen(s)-1]==c){
		return 1;
	}
	else{
		return 0;
	}
}

/*���ƺ���*/
void copy_file(char* source_path,char *destination_path){//�����ļ�
	char buffer[1024];
	FILE *in,*out;//���������ļ������ֱ������ļ��Ķ�ȡ��д��int len;
	if((in=fopen(source_path,"r"))==NULL){//��Դ�ļ����ļ���
		printf("fopen source_path error\n");
		exit(1);
	}
	if((out=fopen(destination_path,"w"))==NULL){//��Ŀ���ļ����ļ���
		printf("fopen destination_path error\n");
		exit(1);
	}
	int len;//lenΪfread�������ֽڳ�
	while((len=fread(buffer,1,1024,in))>0){//��Դ�ļ��ж�ȡ���ݲ��ŵ��������У��ڶ�������1Ҳ����д��sizeof(char)
		fwrite(buffer,1,len,out);//��������������д��Ŀ���ļ���
	}
	fclose(out);
	fclose(in);
}

void process_dir(char *source_path, char *destination_path){
    struct dirent* filename;
    DIR* dp=opendir(source_path);//��DIRָ��ָ������ļ���

    // ����Ŀ���ļ���
    if(!opendir(destination_path)){
        if(mkdir(destination_path, 0777) == -1){
            perror("mkdir");
            return;
        }
    }
    while(filename=readdir(dp)){//����DIRָ��ָ����ļ��У�Ҳ�����ļ����顣
        char *file_source_path, *file_destination_path;
        file_source_path = (char*)malloc(512);
        file_destination_path = (char*)malloc(512);
        //ȡ�ļ����뵱ǰ�ļ���ƴ�ӳ�һ��������·��
        file_source_path=str_contact(file_source_path,source_path);
        file_source_path=str_contact(source_path,"/");
        file_source_path=str_contact(file_source_path,filename->d_name);
        file_destination_path=str_contact(file_destination_path,destination_path);
        file_destination_path=str_contact(destination_path,"/");
        file_destination_path=str_contact(file_destination_path,filename->d_name);

        if(is_dir(file_source_path)){ //�����Ŀ¼
            if(endwith(file_source_path,'.')){//ͬʱ������.��β����ΪLinux�������ļ��ж���һ��.�ļ�������������һ��Ŀ¼�������޳���������еݹ�Ļ�������޷�����
                continue;
            }
            process_dir(file_source_path,file_destination_path);//���еݹ���ã��൱�ڽ�������ļ��н��и��ơ�
        }
        else{
            process_file(file_source_path,file_destination_path);//�����յ�һ�ļ��ĸ��Ʒ������и��ơ�
        }
    }
}

int main(int argc, char * argv[])
{
    if(argc != 3){
        fprintf(stderr, "Usage: %s <in_dir> <out_dir>\n",argv[0] );
        exit(3);
    }

    char *source_path = argv[1];        //Դ·��
    char* destination_path=argv[2];     //Ŀ��·��

    DIR* source=opendir(source_path);
    DIR* destination=opendir(destination_path);
    if(!source){
        printf("source is not a directory\n");
        return -1;
    }

    if(destination){
        printf("destination already exists\n");
        return -1;
    }

    process_dir(source_path, destination_path);

    return 0;
}

