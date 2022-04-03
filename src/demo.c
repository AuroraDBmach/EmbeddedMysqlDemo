#include <stdio.h> 
#include <stdlib.h> 
#include <stdarg.h> 
#include "mysql.h" 
#include "debug.h"

MYSQL *mysql;
MYSQL_RES *results;
MYSQL_ROW record;

// /home/mach/mariadb/10.9/demo/embedded
static char *server_options[] = { 
	"embdb_server1", 
	// "--debug", 
	//"--no-defaults", 
	"--defaults-file=/home/mach/mariadb/10.9/demo/embedded/embdb.conf", 
	//"--print-defaults", 
	"--basedir=/home/mach/mariadb/10.9/demo/embedded/", 
	//"--defaults-file=./embdb.conf", 
	"--datadir=/home/mach/mariadb/10.9/demo/embedded/storage/", 
	"--lc-messages-dir=/home/mach/mariadb/10.9/demo/embedded/share/", 
	// "--language=/home/mach/Test/mariadb-10.1.7/embedded/share/english", 
	// "--console", 
	// "--skip-innodb", 
	"--innodb=OFF", 
	"--default_storage_engine=aria", 
	NULL 
};

int num_elements = (sizeof(server_options) / sizeof(char *)) - 1;

static char *server_groups[] = { 
	"embdb_server1", 
	"embdb_client1", 
	NULL 
};
int main(void) 
{ 
	int retval;

	DEBUG("Num_elements = %d\n", num_elements);

	if ((retval=mysql_library_init(num_elements, server_options, server_groups)) != 0) { 
		DEBUG("Could not initialize MySQL Library : with errno = %d\n", retval);
		DEBUG("Embedded server initialization failure : [%d][%s]\n", mysql_errno(NULL), mysql_error(NULL));
		// exit(1);
	}
	mysql = mysql_init(NULL);
	if ( mysql == (MYSQL *)0) 
		{ DEBUG("ERROR:mysql_init() fail....[%d][%s]\n", mysql_errno(NULL), mysql_error(mysql));
		exit(1);
	}
	
	DEBUG("ERR:[%s]", mysql_error(mysql));
	DEBUG("HERE.................\n");
	
	mysql_options(mysql, MYSQL_READ_DEFAULT_FILE, "embdb.conf");
	mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "embdb_client1");
	
	DEBUG("HERE.................\n");
	DEBUG("ERR:[%s]", mysql_error(mysql));
	mysql_options(mysql, MYSQL_OPT_USE_EMBEDDED_CONNECTION, NULL);
	DEBUG("ERR:[%s]", mysql_error(mysql));
	
	if (! mysql_real_connect(mysql, NULL,NULL,NULL, "futuredb", 0,NULL,0) ) { ;
		DEBUG("$$$$$$$ Failed to connect to database: Error: %s\n", mysql_error(mysql));
	} 
	DEBUG("ERR:[%s]", mysql_error(mysql));
	
	mysql_query(mysql, "INSTALL PLUGIN HandlerSocket SONAME 'handlersocket.so';");
	DEBUG("ERR:[%s]", mysql_error(mysql));
	
	mysql_query(mysql, "SHOW PLUGINS;");
	DEBUG("ERR:[%s]", mysql_error(mysql));
	
	results = mysql_store_result(mysql);
	DEBUG("1\n");
	
	while((record = mysql_fetch_row(results))) { 
		printf("%s - %s \n", record[0], record[1]);
	} 
	mysql_free_result(results);
	////////////// 
	mysql_query(mysql, "SHOW VARIABLES;");
	DEBUG("ERR:[%s]", mysql_error(mysql));
	
	results = mysql_store_result(mysql);
	DEBUG("1\n");
	
	while((record = mysql_fetch_row(results))) { 
		printf("%s - %s \n", record[0], record[1]);
	} 
	mysql_free_result(results);
	//////////////

	mysql_query(mysql, "CREATE TABLE IF NOT EXISTS table1 ( column1 int, column2 int) engine = aria");
	DEBUG("ERR:[%s]", mysql_error(mysql));
	mysql_query(mysql, "INSERT INTO table1 ( column1, column2) VALUES (1,1),(2,2);");
	DEBUG("ERR:[%s]", mysql_error(mysql));
	mysql_query(mysql, "SELECT column1, column2 FROM table1");
	DEBUG("ERR:[%s]", mysql_error(mysql));
	
	results = mysql_store_result(mysql);
	DEBUG("1\n");
	
	while((record = mysql_fetch_row(results))) { 
		printf("%s - %s \n", record[0], record[1]);
	}
	
	DEBUG("1\n");
	mysql_free_result(results);
	mysql_close(mysql);
	mysql_library_end();
	
	return 0;
}
