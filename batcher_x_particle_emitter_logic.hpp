#ifndef BATCHER_X_PARTICLE_EMITTER_LOGIC_HPP
#define BATCHER_X_PARTICLE_EMITTER_LOGIC_HPP

#include <unordered_map>

#include "sbpt_generated_includes.hpp"

struct pair_hash {
    std::size_t operator()(const std::pair<int, int> &p) const {
        return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) * 31);
    }
};

class BatcherXParticleEmitterLogic {
  public:
    TexturePacker &texture_packer;
    BoundedUniqueIDGenerator &ltw_object_id_generator;
    Batcher &batcher;

    draw_info::TransformedIVPTPGroup smoke_tig_for_copying;

    BatcherXParticleEmitterLogic(TexturePacker &texture_packer, BoundedUniqueIDGenerator &ltw_object_id_generator,
                                 Batcher &batcher, ResourcePath &resource_path);

    using EmitterAndParticleIDPair = std::pair<int, int>;
    std::unordered_map<EmitterAndParticleIDPair, draw_info::TransformedIVPTPGroup, pair_hash> particle_id_to_tig;

    void on_particle_death(int emitter_id, int particle_id);
    void on_particle_spawn(int emitter_id, int particle_id);

    void draw_particles(ParticleEmitter &particle_emitter, FPSCamera &fps_camera, double delta_time,
                        glm::mat4 projection, glm::mat4 view);
};

#endif // BATCHER_X_PARTICLE_EMITTER_LOGIC_HPP
