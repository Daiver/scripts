-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Июл 07 2012 г., 15:50
-- Версия сервера: 5.5.24
-- Версия PHP: 5.3.10-1ubuntu3.2

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `knowledge`
--

-- --------------------------------------------------------

--
-- Структура таблицы `articles`
--

CREATE TABLE IF NOT EXISTS `articles` (
  `ar_id` int(11) NOT NULL AUTO_INCREMENT,
  `ar_type` int(11) NOT NULL,
  `ar_value` int(11) NOT NULL,
  PRIMARY KEY (`ar_id`),
  KEY `ar_type` (`ar_type`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `articles`
--

INSERT INTO `articles` (`ar_id`, `ar_type`, `ar_value`) VALUES
(1, 1, 1),
(2, 1, 2);

-- --------------------------------------------------------

--
-- Структура таблицы `article_types`
--

CREATE TABLE IF NOT EXISTS `article_types` (
  `at_id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`at_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Дамп данных таблицы `article_types`
--

INSERT INTO `article_types` (`at_id`, `name`) VALUES
(1, 'textarticle');

-- --------------------------------------------------------

--
-- Структура таблицы `k2a_links`
--

CREATE TABLE IF NOT EXISTS `k2a_links` (
  `k2al_id` int(11) NOT NULL AUTO_INCREMENT,
  `kw_id` int(11) NOT NULL,
  `ar_id` int(11) NOT NULL,
  `weight` int(11) NOT NULL,
  PRIMARY KEY (`k2al_id`),
  KEY `kw_id` (`kw_id`,`ar_id`),
  KEY `ar_id` (`ar_id`),
  KEY `ar_id_2` (`ar_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Дамп данных таблицы `k2a_links`
--

INSERT INTO `k2a_links` (`k2al_id`, `kw_id`, `ar_id`, `weight`) VALUES
(1, 1, 1, 1),
(2, 2, 2, 1),
(3, 1, 2, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `keywords`
--

CREATE TABLE IF NOT EXISTS `keywords` (
  `kw_id` int(11) NOT NULL AUTO_INCREMENT,
  `word` varchar(255) NOT NULL,
  PRIMARY KEY (`kw_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `keywords`
--

INSERT INTO `keywords` (`kw_id`, `word`) VALUES
(1, 'c++'),
(2, 'python');

-- --------------------------------------------------------

--
-- Структура таблицы `text_articles`
--

CREATE TABLE IF NOT EXISTS `text_articles` (
  `ta_id` int(11) NOT NULL AUTO_INCREMENT,
  `text` longtext NOT NULL,
  PRIMARY KEY (`ta_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `text_articles`
--

INSERT INTO `text_articles` (`ta_id`, `text`) VALUES
(1, 'Some info about C++'),
(2, 'something about python');

--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `articles`
--
ALTER TABLE `articles`
  ADD CONSTRAINT `articles_ibfk_1` FOREIGN KEY (`ar_type`) REFERENCES `article_types` (`at_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `k2a_links`
--
ALTER TABLE `k2a_links`
  ADD CONSTRAINT `k2a_links_ibfk_1` FOREIGN KEY (`kw_id`) REFERENCES `keywords` (`kw_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `k2a_links_ibfk_3` FOREIGN KEY (`ar_id`) REFERENCES `articles` (`ar_id`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
