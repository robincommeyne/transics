/*! \file */

#include <QString>
#include "logging.h"
#include "watchdog.h"
#include <QDebug>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/support/date_time.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace expr = boost::log::expressions;



void Logging::Log(QString Loglevel,QString message)
{

  logging::add_common_attributes();
  using namespace logging::trivial;
  src::severity_logger<severity_level> lg;

  if(Loglevel == "trace")
  {
   BOOST_LOG_SEV(lg,trace) << message.toStdString();
  }
  else if(Loglevel == "debug")
  {
    BOOST_LOG_SEV(lg,debug) << message.toStdString();
  }
  else if(Loglevel == "info")
  {
    BOOST_LOG_SEV(lg,info) << message.toStdString();
  }
  else if(Loglevel == "warning")
  {
    BOOST_LOG_SEV(lg,warning) << message.toStdString();
  }
  else if(Loglevel == "error")
  {
    BOOST_LOG_SEV(lg,error) << message.toStdString();
  }
  else if(Loglevel == "fatal")
  {
    BOOST_LOG_SEV(lg,fatal) << message.toStdString();
  }
  else
  {
      qDebug() << "loglevel not supported";
  }


}

void Logging::InitLogging(int RotationInterval,int Filesize)
{
   int MaxFolderSize = 10*1024*1024; // MegaBytes


  logging::add_file_log(
               keywords::file_name = "system.log",
               keywords::rotation_size = Filesize*1024*1024,
               keywords::target = "Logs",
               keywords::time_based_rotation = sinks::file::rotation_at_time_interval(boost::posix_time::hours(RotationInterval)),
               keywords::format =
           (
               expr::stream
               << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
               << ": <" << logging::trivial::severity
               << "> " << expr::smessage
               ),
               keywords::auto_flush = true,
               keywords::scan_method = boost::log::sinks::file::scan_matching,
               keywords::open_mode = std::ios::app

           )->locked_backend()->set_file_collector
           ( sinks::file::make_collector
             ( keywords::target = "Logs",
               keywords::max_size = MaxFolderSize
           )
            );


    logging::core::get()->set_filter
        (
            logging::trivial::severity >= logging::trivial::info
        );

}
