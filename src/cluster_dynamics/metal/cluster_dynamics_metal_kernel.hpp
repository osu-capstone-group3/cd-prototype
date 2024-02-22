#ifndef CLUSTER_DYNAMICS_METAL_ARGS_HPP
#define CLUSTER_DYNAMICS_METAL_ARGS_HPP

#include "material_impl.hpp"
#include "nuclear_reactor_impl.hpp"

#if defined(__METAL__)
#define __METALDECL__ device
#define mtl_math metal::precise
#else
#include <cstdint>
#define __METALDECL__
#define mtl_math std
#endif

class ClusterDynamicsMetalKernel {
 public:
    __METALDECL__ NuclearReactorImpl* reactor;
    __METALDECL__ MaterialImpl* material;

    __METALDECL__ gp_float* interstitials;
    __METALDECL__ gp_float* vacancies;

    uint64_t concentration_boundary;
    gp_float dislocation_density;
    gp_float delta_time;

    gp_float mean_dislocation_radius_val;
    gp_float ii_sum_absorption_val;
    gp_float iv_sum_absorption_val;
    gp_float vv_sum_absorption_val;
    gp_float vi_sum_absorption_val;
    gp_float i_diffusion_val;
    gp_float v_diffusion_val;

    // Physics Model Functions
    gp_float i_concentration_derivative(uint64_t) __METALDECL__;
    gp_float v_concentration_derivative(uint64_t) __METALDECL__;
    gp_float i1_concentration_derivative() __METALDECL__;
    gp_float v1_concentration_derivative() __METALDECL__;
    gp_float dislocation_density_derivative() __METALDECL__;
    gp_float i_defect_production(uint64_t) __METALDECL__;
    gp_float v_defect_production(uint64_t) __METALDECL__;
    gp_float iemission_vabsorption_np1(uint64_t) __METALDECL__;
    gp_float vemission_iabsorption_np1(uint64_t) __METALDECL__;
    gp_float iemission_vabsorption_n(uint64_t) __METALDECL__;
    gp_float vemission_iabsorption_n(uint64_t) __METALDECL__;
    gp_float iemission_vabsorption_nm1(uint64_t) __METALDECL__;
    gp_float vemission_iabsorption_nm1(uint64_t) __METALDECL__;
    gp_float i_emission_rate() __METALDECL__;
    gp_float v_emission_rate() __METALDECL__;
    gp_float i_absorption_rate() __METALDECL__;
    gp_float v_absorption_rate() __METALDECL__;
    gp_float annihilation_rate() __METALDECL__;
    gp_float i_dislocation_annihilation_rate() __METALDECL__;
    gp_float v_dislocation_annihilation_rate() __METALDECL__;
    gp_float i_grain_boundary_annihilation_rate() __METALDECL__;
    gp_float v_grain_boundary_annihilation_rate() __METALDECL__;
    gp_float ii_emission(uint64_t) __METALDECL__;
    gp_float vv_emission(uint64_t) __METALDECL__;
    gp_float ii_absorption(uint64_t) __METALDECL__;
    gp_float iv_absorption(uint64_t) __METALDECL__;
    gp_float vi_absorption(uint64_t) __METALDECL__;
    gp_float vv_absorption(uint64_t) __METALDECL__;
    gp_float i_bias_factor(uint64_t) __METALDECL__;
    gp_float v_bias_factor(uint64_t) __METALDECL__;
    gp_float i_binding_energy(uint64_t) __METALDECL__;
    gp_float v_binding_energy(uint64_t) __METALDECL__;
    gp_float dislocation_promotion_probability(uint64_t) __METALDECL__;
    gp_float cluster_radius(uint64_t) __METALDECL__;

    // Value Precalculation Functions
    gp_float i_diffusion() __METALDECL__;
    gp_float v_diffusion() __METALDECL__;
    gp_float ii_sum_absorption(uint64_t) __METALDECL__;
    gp_float iv_sum_absorption(uint64_t) __METALDECL__;
    gp_float vv_sum_absorption(uint64_t) __METALDECL__;
    gp_float vi_sum_absorption(uint64_t) __METALDECL__;
    gp_float mean_dislocation_cell_radius() __METALDECL__;

    void step_init() __METALDECL__;
    bool update_clusters_1(gp_float) __METALDECL__;
};

#endif  // CLUSTER_DYNAMICS_METAL_ARGS_HPP