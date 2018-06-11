-- --------------------------------------------------------
-- 主机:                           127.0.0.1
-- 服务器版本:                        5.7.19-log - MySQL Community Server (GPL)
-- 服务器操作系统:                      Win64
-- HeidiSQL 版本:                  9.5.0.5196
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- 导出 water 的数据库结构
CREATE DATABASE IF NOT EXISTS `water` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `water`;

-- 导出  表 water.item 结构
CREATE TABLE IF NOT EXISTS `item` (
  `TestID` int(11) DEFAULT NULL,
  `Reagent0` int(11) DEFAULT NULL,
  `Time0` int(11) DEFAULT NULL,
  `Volume0` int(11) DEFAULT NULL,
  `Reagent1` int(11) DEFAULT NULL,
  `Time1` int(11) DEFAULT NULL,
  `Volume1` int(11) DEFAULT NULL,
  `Reagent2` int(11) DEFAULT NULL,
  `Time2` int(11) DEFAULT NULL,
  `Volume2` int(11) DEFAULT NULL,
  `Reagent3` int(11) DEFAULT NULL,
  `Time3` int(11) DEFAULT NULL,
  `Volume3` int(11) DEFAULT NULL,
  `Reagent4` int(11) DEFAULT NULL,
  `Time4` int(11) DEFAULT NULL,
  `Volume4` int(11) DEFAULT NULL,
  `Priority` int(11) DEFAULT NULL,
  `zsypkb` int(11) DEFAULT NULL,
  `ReplaceReagent` int(11) DEFAULT NULL,
  `method` int(11) DEFAULT NULL,
  `readstep` int(11) DEFAULT NULL,
  `readInterval` int(11) DEFAULT NULL,
  `readtimes` int(11) DEFAULT NULL,
  `wavenum` int(11) DEFAULT NULL,
  `wl0` int(11) DEFAULT NULL,
  `wl1` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='项目信息，项目流程，项目重做';

-- 数据导出被取消选择。
-- 导出  表 water.sr 结构
CREATE TABLE IF NOT EXISTS `sr` (
  `testsn` varchar(50) NOT NULL,
  `testpageid` varchar(50) NOT NULL,
  `id` varchar(50) NOT NULL,
  `sampleid` varchar(50) NOT NULL,
  `isPredilute` tinyint(4) NOT NULL,
  `Predilutetimes` int(11) NOT NULL,
  `Pos` int(11) NOT NULL,
  `Samplecuptype` tinyint(4) NOT NULL,
  `Isurgent` tinyint(4) NOT NULL,
  `Testtype` tinyint(4) NOT NULL,
  `Qualityname` varchar(50) NOT NULL,
  `Caname` varchar(50) NOT NULL,
  `IsDilute` tinyint(4) NOT NULL,
  `DiluteVolume` int(11) NOT NULL,
  `Dilutetimes` int(11) NOT NULL,
  `Dilutetime` int(11) NOT NULL,
  `TestID` int(11) NOT NULL,
  `Isreplace` int(11) NOT NULL,
  `Stage` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='样本测试登记';

-- 数据导出被取消选择。
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
