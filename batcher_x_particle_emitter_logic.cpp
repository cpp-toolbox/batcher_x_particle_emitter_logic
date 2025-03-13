#include "batcher_x_particle_emitter_logic.hpp"

BatcherXParticleEmitterLogic::BatcherXParticleEmitterLogic(TexturePacker &texture_packer,
                                                           BoundedUniqueIDGenerator &ltw_object_id_generator,
                                                           Batcher &batcher, ResourcePath &resource_path)
    : texture_packer(texture_packer), ltw_object_id_generator(ltw_object_id_generator), batcher(batcher) {

    // TODO: need to use gfp here? yes, also note that this requires the smoke texture or else things will go wrong
    auto smoke_filepath = resource_path.gfp("assets/images/smoke_64px.png").string();
    auto smoke_st = texture_packer.get_packed_texture_sub_texture(smoke_filepath);

    auto vertices = vertex_geometry::generate_square_vertices(0, 0, 0.5);
    auto indices = vertex_geometry::generate_rectangle_indices();

    draw_info::IVPTexturePacked smoke_ivptp(
        indices, vertices, smoke_st.texture_coordinates, smoke_st.texture_coordinates, smoke_st.packed_texture_index,
        smoke_st.packed_texture_bounding_box_index, smoke_filepath,
        batcher.texture_packer_cwl_v_transformation_ubos_1024_shader_batcher.object_id_generator.get_id());

    smoke_tig_for_copying = draw_info::TransformedIVPTPGroup({smoke_ivptp}, -1);
}
