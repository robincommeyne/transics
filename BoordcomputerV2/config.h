#ifndef CONFIG_H
#define CONFIG_H

#include <QMap>

namespace cangateway {

    class Config
    {
        public:

            Config();

            void set_readinterval(int readinterval){ReadInterval = readinterval;}
            int get_readinterval() const { return ReadInterval; }

            void set_configmap(QMap<QString, bool> configmap){Configmap = configmap;}
            QMap<QString, bool> get_configmap() const {return Configmap;}

        private:
            QMap<QString, bool> Configmap;
            int ReadInterval;

    };

}

#endif // CONFIG_H
