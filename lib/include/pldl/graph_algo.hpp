// -*- coding: utf-8 -*-
#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>

namespace pldl
{

/*!
 * @brief minimum weighted vertex cover problem
 *
 *    This function solves minimum vertex cover problem
 *    using primal-dual paradigm:
 *
 * @tparam Graph
 * @tparam Container
 * @param[in] G
 * @param[in] weight
 * @param[in,out] cover initial: pre-covered vetrices
 * @return C1::value_type total cost
 */
template <typename Graph, typename C1, typename C2>
auto min_vertex_cover(const Graph& G, const C1& weight, C2& cover) ->
    typename C1::mapped_type
{
    using T = typename C1::mapped_type;

    [[maybe_unused]] auto total_dual_cost = T(0);
    auto total_primal_cost = T(0);
    auto gap = weight;
    for (auto&& e : G.edges())
    {
        auto [u, v] = G.end_points(e);
        if (cover.contains(u) || cover.contains(v))
        {
            continue;
        }
        if (gap[u] < gap[v])
        {
            std::swap(u, v);
        }
        cover.insert(v);
        total_dual_cost += gap[v];
        total_primal_cost += weight[v];
        gap[u] -= gap[v];
        gap[v] = T(0);
    }

    assert(total_dual_cost <= total_primal_cost);
    assert(total_primal_cost <= 2 * total_dual_cost);
    return total_primal_cost;
}


/**
 * @brief minimum weigthed maximal independant set problem
 *
 *    This function solves minimum weighted maximal independant set problem
 *    using primal-dual approximation algorithm:
 *
 * @tparam Graph
 * @tparam C1
 * @tparam C2
 * @param[in] G
 * @param[in] weight
 * @param[in,out] indset
 * @param[in,out] dep
 * @return C1::value_type
 */
template <typename Graph, typename C1, typename C2>
auto min_maximal_independant_set(const Graph& G, const C1& weight, C2& indset,
    C2& dep) -> typename C1::mapped_type
{
    using T = typename C1::mapped_type;

    auto cover = [&](const auto& u)
    {
        dep.insert(u);
        for (auto&& v : G[u])
        {
            dep.insert(v);
        }
    };

    auto gap = weight;
    [[maybe_unused]] auto total_dual_cost = T(0);
    auto total_primal_cost = T(0);
    for (auto&& u : G)
    {
        if (dep.contains(u))
        {
            continue;
        }
        if (indset.contains(u))
        { // pre-define independant
            cover(u);
            continue;
        }
        auto min_val = gap[u];
        auto min_vtx = u;
        for (auto&& v : G[u])
        {
            if (dep.contains(v))
            {
                continue;
            }
            if (min_val > gap[v])
            {
                min_val = gap[v];
                min_vtx = v;
            }
        }
        cover(min_vtx);
        indset.insert(min_vtx);
        total_primal_cost += weight[min_vtx];
        total_dual_cost += min_val;
        if (min_vtx != u)
        {
            for (auto&& v : G[u])
            {
                gap[v] -= min_val;
            }
        }
    }
    assert(total_dual_cost <= total_primal_cost);
    return total_primal_cost;
}

} // namespace pldl
