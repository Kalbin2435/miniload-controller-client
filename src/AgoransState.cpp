#include <mutex>
#include "enums.hpp"
#include "AgoransState.hpp"

namespace main_window {
    class AgoransState {
        public:
            static AgoransState& getInstance() {
                static AgoransState* instance = new AgoransState();
                return *instance;
            }
        private:
            AgoransState() {
            }

            void FetchAgoransData() {
                // load data of active warehouse from database
                // start up agorans as many as in active warehouse
                // nothing else can ever change the active warehouse again :)
                // make getter that allowes getting information about current active warehouse
            }

            struct Agoran {
                int agoran_id;
                AgoranStatus status;
                AgoranMode mode;
                int loaded_tray;
                int left_workstation_loaded_tray;
                int right_workstation_loaded_tray;
            };


            ~AgoransState() {
                /*
                defined deconstructor as private
                to prevent someone( future me :) )
                from forgetting about it and
                accidently calling the destructor
                */
            }
    };
}
