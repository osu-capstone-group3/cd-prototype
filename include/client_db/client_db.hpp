#ifndef CLIENT_DB_HPP
#define CLIENT_DB_HPP

#include <vector>
#include <sqlite3.h>
#include "gpies_exception.hpp"

class NuclearReactor;
class Material;

static const char* DEFAULT_CLIENT_DB_PATH = "./db/gpies.db";

class ClientDb
{
public:

    // Initializes and opens the SQLite database, followed by any needed schema maintenance.
    // |sqlite_code| can optionally be retrieved.
    // Returns true on success.
    bool init(int* sqlite_code = nullptr);

    // Drops all tables in the SQLite database.
    // *** WARNING *** All data will be lost.
    // |sqlite_code| can optionally be retrieved.
    // Returns true on success.
    bool clear(int* sqlite_code = nullptr);

    // --------------------------------------------------------------------------------------------
    // REACTOR CRUD

    // Creates a reactor in the local database, assigning a value to NuclearReactor.sqlite_id.
    // |sqlite_code| can optionally be retrieved.
    // Returns true on success.
    bool create_reactor(NuclearReactor& reactor, int* sqlite_code = nullptr);

    // Reads all reactors from the local database, populating |reactors|.
    // |sqlite_code| can optionally be retrieved.
    // Returns true on success.
    bool read_reactors(std::vector<NuclearReactor>& reactors, int* sqlite_code = nullptr);

    // Attempts to read a single |reactor| from the local database, matching the specified |sqlite_id|.
    // |sqlite_code| can optionally be retrieved.
    // Returns true on success.
    bool read_reactor(const int sqlite_id, NuclearReactor& reactor, int* sqlite_code = nullptr);

    // Attempts to update a reactor in the local database, matching to |reactor.sqlite_id|.
    // |sqlite_code| can optionally be retrieved.
    // Returns true on success.
    bool update_reactor(const NuclearReactor& reactor, int* sqlite_code = nullptr);

    // Attempts to delete a reactor in the local database, matching to |reactor.sqlite_id|.
    // |sqlite_code| can optionally be retrieved.
    // Returns true on success.
    bool delete_reactor(const NuclearReactor& reactor, int* sqlite_code = nullptr);

    // --------------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------------
    // MATERIAL CRUD
    // --------------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------------
    // SIMULATION CRUD
    // --------------------------------------------------------------------------------------------

    // |sqlite_code| can optionally be retrieved.
    // Returns true on success.
    bool open(int* sqlite_code = nullptr);

    // |sqlite_code| can optionally be retrieved.
    // Returns true on success.
    bool close(int* sqlite_code = nullptr);

    // Returns true if the SQLite database is currently open.
    bool is_open();

    // Returns true if |sqlite_code| reprents a successful result.
    // https://www.sqlite.org/rescode.html
    static bool is_sqlite_success(const int sqlite_code);

    // Returns true if |sqlite_code| reprents a successful result.
    // https://www.sqlite.org/rescode.html
    static bool is_sqlite_error(const int sqlite_code);

    // Returns true if |sqlite_id| is a value primary key value.
    // NOTE: This does NOT check if |sqlite_id| exists within the database.
    static bool is_valid_sqlite_id(const int sqlite_id);

    // Specify the |db_path| where the SQLite database resides
    // |lazy| will wait to open the database until |init| is called.
    ClientDb(const char* db_path = DEFAULT_CLIENT_DB_PATH, const bool lazy = true);
    ~ClientDb();

private:
    // The SQLite database reference.
    sqlite3* db;

    // The path to the SQLite database which |db| will reference.
    std::string path;

    // Returns the last inserted row id, regardless of the table.
    int last_insert_rowid(int&);


    // --------------------------------------------------------------------------------------------
    /*  TEMPLATE FUNCTIONS
        These are called by the public facing functions, implementing the basic logic of statement
        execution and exception handling for create, read, update and delete. All functions return
        the resulting SQLite status code.
    */

    // CREATE
    template<typename T> int create_one(sqlite3_stmt*, void (*)(sqlite3_stmt*, const T&), T&);

    // READ 
    template<typename T> int read_one(sqlite3_stmt*, void (*)(sqlite3_stmt*, T&), void (*)(sqlite3_stmt*, const int), const int, T&);
    template<typename T> int read_all(sqlite3_stmt*, void (*)(sqlite3_stmt*, T&), void (*)(sqlite3_stmt*), std::vector<T>&);

    // UPDATE / DELETE
    template<typename T> int update_one(sqlite3_stmt*, void (*)(sqlite3_stmt*, const T&), const T&);

    // DELETE 
    template<typename T> int delete_one(sqlite3_stmt*, void (*)(sqlite3_stmt*, const T&), const T&);

    // --------------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------------
    /*  COLUMN BINDING
        These are called by the public facing function to bind objects to SQLite statements.
    */
    static void bind_reactor(sqlite3_stmt*, const NuclearReactor&);
    // --------------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------------
    /*  ROW CALLBACKS 
        These callbacks are used as parameters in the read template functions. They handle the
        underlying logic of copying data from a retrieved SQLite row into an object.
    */
    static void row_read_reactor(sqlite3_stmt*, NuclearReactor&);
    // --------------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------------
    /*  ERROR CALLBACKS 
        These callbacks are used as parameters in all template functions to handle any errors that
        occur in the database queries.
    */
    static void err_create_reactor(sqlite3_stmt*, const NuclearReactor&);
    static void err_read_reactors(sqlite3_stmt*);
    static void err_read_reactor(sqlite3_stmt*, const int);
    static void err_update_reactor(sqlite3_stmt*, const NuclearReactor&);
    static void err_delete_reactor(sqlite3_stmt*, const NuclearReactor&);
    // --------------------------------------------------------------------------------------------
};

class ClientDbException : public GpiesException
{
    public:
    ClientDbException(const std::string& message, const std::string& sqlite_errmsg = "", const int sqlite_code = -1, const std::string& query = "")
    : GpiesException(message), sqlite_errmsg(sqlite_errmsg), sqlite_code(sqlite_code), query(query)
    {
    }

    std::string sqlite_errmsg;
    int sqlite_code;
    std::string query;
};

#endif // CLIENT_DB_HPP