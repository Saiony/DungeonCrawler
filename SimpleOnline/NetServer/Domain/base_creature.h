    #pragma once

    namespace dungeon_server::domain
    {
        class base_creature
        {
        public:
            virtual ~base_creature(){}
            std::string public_id;
        };
    }