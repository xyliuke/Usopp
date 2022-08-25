//
// Created by liuke on 2022/8/25.
//

#include "video_render.h"
#include "shape.h"
#include "shader.h"
#include "texture.h"

namespace plan9
{
    class video_render::video_render_impl {
    public:
        video_render_impl(const std::string &vertex_file_path, const std::string &fragment_file_path) {
            glewInit();
            shape = std::make_shared<plan9::shape>();
            shader = std::make_shared<plan9::shader>(vertex_file_path, fragment_file_path);
            texture = std::make_shared<plan9::texture>();
            texture_id = 0;
        }
        /**
         * 创建显示区域大小，（lx,ly)是左上角坐标,范围为[0, 1); (rx,ry)是右下角坐标,范围是(0, 1]，lx < rx, ly < ry
         * @param lx
         * @param ly
         * @param rx
         * @param ry
         */
        void create(float lx, float ly, float rx, float ry, int vertex_location, int texture_location) {
            shader->compile();

            shape->set_vertex_num(4);
            shape->set_vertex(0, rx, ly, 0.f);
            shape->set_vertex(1, rx, ry, 0.f);
            shape->set_vertex(2, lx, ry, 0.f);
            shape->set_vertex(3, lx, ly, 0.f);

            shape->set_triangle_num(2);
            shape->set_vertex_index(0, 0, 1, 3);
            shape->set_vertex_index(1, 1, 2, 3);

            shape->set_vertex_texture(0, 1.f, 1.f);
            shape->set_vertex_texture(1, 1.f, 0.f);
            shape->set_vertex_texture(2, 0.f, 0.f);
            shape->set_vertex_texture(3, 0.f, 1.f);

            shape->create(vertex_location, texture_location);
        }

        void update(const std::string &path) {
            texture->update(path);
            shader->set_uniform_value("ourTexture", 0);
        }

        void render() {
            texture->use(texture_id);
            shader->use();
            shape->render();
        }


    private:
        int texture_id;
        std::shared_ptr<plan9::shape> shape;
        std::shared_ptr<plan9::shader> shader;
        std::shared_ptr<plan9::texture> texture;
    };

    video_render::video_render(const std::string &vertex_file_path, const std::string &fragment_file_path) {
        impl = std::make_shared<video_render_impl>(vertex_file_path, fragment_file_path);
    }

    void video_render::create(float lx, float ly, float rx, float ry, int vertex_location, int texture_location) {
        impl->create(lx, ly, rx, ry, vertex_location, texture_location);
    }

    void video_render::update(const std::string &path) {
        impl->update(path);
    }

    void video_render::render() {
        impl->render();
    }
}