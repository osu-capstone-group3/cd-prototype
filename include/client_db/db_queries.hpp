#ifndef DB_QUERIES_HPP
#define DB_QUERIES_HPP


#include <string>

namespace db_queries 
{

/*  SCHEMA
    in SQLite, AUTOINCREMENT on PRIMARY KEYs only prevents the reuse of ROWIDs
    which have not been used. The macro is omitted to avoid unnecessary overhead.
    https://www.sqlite.org/autoinc.html
*/
std::string init =
    "CREATE TABLE IF NOT EXISTS reactors"
    "("
        "id_reactor INTEGER PRIMARY KEY AUTOINCREMENT,"
        "creation_datetime TEXT DEFAULT current_timestamp,"
        "species text NOT NULL DEFAULT '',"
        "flux float DEFAULT 0.0,"
        "temperature float DEFAULT 0.0,"
        "recombination float DEFAULT 0.0,"
        "i_bi float DEFAULT 0.0,"
        "i_tri float DEFAULT 0.0,"
        "i_quad float DEFAULT 0.0,"
        "v_bi float DEFAULT 0.0,"
        "v_tri float DEFAULT 0.0,"
        "v_quad float DEFAULT 0.0,"
        "dislocation_density_evolution float DEFAULT 0.0"
    ");"

    "CREATE TABLE IF NOT EXISTS materials"
    "("
        "id_material INTEGER PRIMARY KEY,"
        "creation_datetime TEXT DEFAULT current_timestamp,"
        "species text NOT NULL DEFAULT '',"
        "i_migration float DEFAULT 0.0,"
        "v_migration float DEFAULT 0.0,"
        "i_diffusion_0 float DEFAULT 0.0,"
        "v_diffusion_0 float DEFAULT 0.0,"
        "i_formation float DEFAULT 0.0,"
        "v_formation float DEFAULT 0.0,"
        "i_binding float DEFAULT 0.0,"
        "v_binding float DEFAULT 0.0,"
        "recombination_radius float DEFAULT 0.0,"
        "i_loop_bias float DEFAULT 0.0,"
        "i_dislocation_bias float DEFAULT 0.0,"
        "i_dislocation_bias_param float DEFAULT 0.0,"
        "v_loop_bias float DEFAULT 0.0,"
        "v_dislocation_bias float DEFAULT 0.0,"
        "v_dislocation_bias_param float DEFAULT 0.0,"
        "dislocation_density_0 float DEFAULT 0.0,"
        "grain_size float DEFAULT 0.0,"
        "lattice_param float DEFAULT 0.0,"
        "burgers_vector float DEFAULT 0.0,"
        "atomic_volume float DEFAULT 0.0"
    ");"

    "CREATE TABLE IF NOT EXISTS simulations"
    "("
        "id_simulation INTEGER PRIMARY KEY,"
        "creation_datetime TEXT DEFAULT current_timestamp,"
        "id_reactor INTEGER,"
        "simulation_time FLOAT DEFAULT 0.0,"
        "time_delta FLOAT DEFAULT 0.0,"
        "data TEXT"
    ");"

    "CREATE TABLE IF NOT EXISTS simulation_materials"
    "("
        "id_simulation NOT NULL,"
        "id_material NOT NULL,"
        "PRIMARY KEY (id_simulation, id_material)"
    ");";

std::string clear =
    "DROP TABLE IF EXISTS simulations;"
    "DROP TABLE IF EXISTS reactors;"
    "DROP TABLE IF EXISTS materials;"
    "DROP TABLE IF EXISTS simulation_materials;";

std::string last_insert_rowid =
    "SELECT last_insert_rowid();";

// reactors CRUD

std::string create_reactor = 
    "INSERT INTO reactors ("
    "species, flux, temperature, recombination, i_bi, i_tri, i_quad, v_bi, v_tri, v_quad, dislocation_density_evolution"
    ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

std::string read_reactors = 
    "SELECT * FROM reactors;";

std::string read_reactor = 
    "SELECT * FROM reactors WHERE id_reactor = ?;";

std::string update_reactor = 
    "UPDATE reactors SET "
    "species = ?, "
    "flux = ?, "
    "temperature = ?, "
    "recombination = ?, "
    "i_bi = ?, "
    "i_tri = ?, "
    "i_quad = ?, "
    "v_bi = ?, "
    "v_tri = ?, "
    "v_quad = ?, "
    "dislocation_density_evolution = ? "
    "WHERE id_reactor = ?;";

std::string delete_reactor = 
    "DELETE FROM reactors WHERE id_reactor = ?;";

// materials CRUD

std::string create_material = 
    "INSERT INTO materials ("
    "species, i_migration, v_migration, i_diffusion_0, v_diffusion_0, i_formation, v_formation, i_binding, v_binding, recombination_radius, i_loop_bias, i_dislocation_bias, i_dislocation_bias_param, v_loop_bias, v_dislocation_bias, v_dislocation_bias_param, dislocation_density_0, grain_size, lattice_param, burgers_vector, atomic_volume"
    ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

std::string read_materials = 
    "SELECT * FROM materials;";

std::string read_material = 
    "SELECT * FROM materials WHERE id_material = ?;";

std::string update_material = 
    "UPDATE materials SET "
    "species = ?, "
    "i_migration = ?, "
    "v_migration = ?, "
    "i_diffusion_0 = ?, "
    "v_diffusion_0 = ?, "
    "i_formation = ?, "
    "v_formation = ?, "
    "i_binding = ?, "
    "v_binding = ?, "
    "recombination_radius = ?, "
    "i_loop_bias = ?, "
    "i_dislocation_bias = ?, "
    "i_dislocation_bias_param = ?, "
    "v_loop_bias = ?, "
    "v_dislocation_bias = ?, "
    "v_dislocation_bias_param = ?, "
    "dislocation_density_0 = ?, "
    "grain_size = ?, "
    "lattice_param = ?, "
    "burgers_vector = ?, "
    "atomic_volume = ? "
    "WHERE id_material = ?;";

std::string delete_material = 
    "DELETE FROM materials WHERE id_material = ?;";

// simulations CRUD

std::string create_simulation = 
    "INSERT INTO simulations ("
    "id_reactor, simulation_time, time_delta, data"
    ") VALUES (?, ?, ?, ?);";

std::string read_simulations = 
    "SELECT * FROM simulations;";

std::string read_simulation = 
    "SELECT * FROM simulations WHERE id_simulation = ?;";

std::string update_simulation = 
    "UPDATE simulations SET "
    "id_reactor = ?, "
    "simulation_time = ?, "
    "time_delta = ?, "
    "data = ? "
    "WHERE id_simulation = ?;";

std::string delete_simulation = 
    "DELETE FROM simulations WHERE id_simulation = ?;";

// simulation_materials CRUD

std::string create_simulation_material = 
    "INSERT INTO simulation_materials ("
    "id_simulation, id_material"
    ") VALUES (?, ?);";

std::string read_simulation_materials = 
    "SELECT * FROM simulation_materials;";

std::string read_simulation_material_by_id_simulation = 
    "SELECT * FROM simulation_materials WHERE id_simulation = ?;";

std::string read_simulation_material_by_id_material = 
    "SELECT * FROM simulation_materials WHERE id_material = ?;";

std::string update_simulation_material = 
    "UPDATE simulation_materials SET "
    "id_simulation = ?, "
    "id_material = ? "
    "WHERE id_simulation = ? "
    "AND id_material = ?;";

std::string delete_simulation_material = 
    "DELETE FROM simulation_materials WHERE id_simulation = ? AND id_material = ?;";
}

#endif