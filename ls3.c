#define	SCREEN_WIDTH	80	/* for now */

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
void do_ls(char []);

//读取参数
main(int ac, char *av[])
{
	if ( ac == 1 )
		do_ls( "." );
	else
		while ( --ac ){
			printf("%s:\n", *++av );
			do_ls( *av );
		}
}


void do_ls( char dirname[] )
/*
 *  *	list files in directory called dirname
 *   */
{
	DIR		*dir_ptr;		/* the directory */
	struct dirent	*direntp;		/* each entry	 */

	list_init();

	if ( ( dir_ptr = opendir( dirname ) ) == NULL )
		fatal("cannot open ", dirname);
	else
	{
		while ( ( direntp = readdir( dir_ptr ) ) != NULL )
			list_append( direntp->d_name );
		closedir(dir_ptr);
	}

	list_show();
	list_finish();
}

/*
 *  * list functions here
 *   *  a list of names is an array that grows as needed
 *    */

void *emalloc(unsigned), *erealloc(void*, unsigned);
char **namelist = NULL;
int  listlen = 0;
int  taken = 0;

#define	CHUNKLEN  100

list_init()
{
	namelist = (char **) emalloc(CHUNKLEN * sizeof(char *));
	listlen = CHUNKLEN;
	taken = 0;
}

/*
 *  * add an item to the list, extending it if needed
 *   */
list_append(char *str)
{
	//函数指针
	char	*newstring(char *);
	//
	char	*name = newstring(str);

	if ( taken == listlen ){
		listlen += CHUNKLEN;
		namelist = (char **) erealloc(namelist,listlen);
	}
	namelist[taken++] = name ;
}

/*
 *  * figure out max length, then figure out number of cols we
 *   * can do and then list them
 *    */
list_show()
{
	int	i;
	int	maxlen = 0;
	int	pagewidth;
	int	cols, col_len, col_wid;
	int	row, col;
	char	*name;

	/* figure out lengths and widths of columns */
	//确定最大字符串的长度
	for(i=0; i<taken; i++)
		if ( strlen(namelist[i]) > maxlen )
			maxlen = strlen(namelist[i]);
	
	//得到每一列的长度
	col_wid = maxlen+1;
	//得到页面的宽度
	pagewidth = get_screen_width();
	//得到列的数目
	cols = pagewidth / col_wid ;
	//达到列的宽度
	col_len = taken / cols ;
	//如果有多余则列的宽度加1
	if ( taken % cols )		/* for uneven cols, put the */
		col_len++;		/* extra on the left	    */

	/* print the list using these numbers */
	// 打印
	for( row = 0 ; row < col_len ; row++ )
		for( col = 0 ; col < cols ; col++ ){
			i = row + col*col_len ;
			if ( i < taken ){
				if ( i + col_len < taken )
					printf("%-*s",col_wid,namelist[i]);
				else
					printf("%s\n",namelist[i]);
			}
		}
}

/*
 *  * delete the words and the list
 *   */
list_finish()
{
	int	i;
	//释放指针
	for(i = 0 ; i<taken ; i++ )
		free(namelist[i]);
	//释放namelist自身
	free(namelist);
	namelist = NULL;
	//重置taken listlen
	taken = listlen = 0 ;
}
	
/*
 *  * in the future, we can ask the system for the width of
 *   * the screen
 *    */
int get_screen_width()
{
	return SCREEN_WIDTH;
}
/*
 *  * construct a string 
 *   */
char *newstring(char *s)
{
	char	*rv = emalloc( 1 + strlen(s) );
	strcpy(rv, s);
	return rv;
}

void *emalloc(unsigned n)
{
	void *rv = malloc(n);
	if ( rv )
		return rv;
	fatal("out of memory","");
}

void *erealloc(void *p, unsigned n)
{
	void *rv = realloc(p,n);
	if ( rv )
		return rv;
	fatal("out of memory","");
}
/*
 *  * report and die
 *   */

fatal(char *s1, char *s2)
{
	fprintf(stderr,"ls1: %s%s\n", s1, s2);
	exit(1);
}
