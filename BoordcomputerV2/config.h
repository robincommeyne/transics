/*! \file */
#ifndef CONFIG_H
#define CONFIG_H

#include <QMap>

namespace cangateway {

    class Config
    {
        public:

            Config();

            void set_readinterval(int readinterval){_readInterval = readinterval;}
            int get_readinterval() const { return _readInterval; }

            void set_configmap(QMap<QString, bool> configmap){_configmap = configmap;}
            QMap<QString, bool> get_configmap() const {return _configmap;}

        private:
            QMap<QString, bool> _configmap;
            int _readInterval;

    };

}

#endif // CONFIG_H
