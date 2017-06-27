-- phpMyAdmin SQL Dump
-- version 3.1.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Dec 14, 2009 at 10:10 PM
-- Server version: 5.1.30
-- PHP Version: 5.2.8

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `haikusite`
--
CREATE DATABASE `haikusite` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `haikusite`;

-- --------------------------------------------------------

--
-- Table structure for table `haiku`
--

CREATE TABLE IF NOT EXISTS `haiku` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `userid` int(11) NOT NULL,
  `title` text NOT NULL,
  `haikuText` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

--
-- Dumping data for table `haiku`
--

INSERT INTO `haiku` (`id`, `userid`, `title`, `haikuText`) VALUES
(1, 2, 'untitled', 'a pomegranate<br>weird thing that looks like a skull<br>maybe melted clocks'),
(2, 1, 'first try', 'here I go writing<br>the first haiku of my life<br>hope it doesnt stink'),
(3, 3, 'Luke’s conversation with yoda', 'Degobah system…<br>Luke says: I am not afraid<br>Yoda: you will be\r\n'),
(4, 3, 'teh internets', 'rofl, lol, rofl<br>i can has teh internets<br>rofl, lol, rofl\r\n'),
(5, 4, 'comp sci', 'Without my comp sci<br>I am adrift in a sea<br>There is no keyboard'),
(6, 4, 'Banana Tree', 'How dreadfully sad<br>The banana tree in winter<br>Pale, dead  and wind-torn\r\n');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` text NOT NULL,
  `email` text NOT NULL,
  `country` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=5 ;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `name`, `email`, `country`) VALUES
(1, 'Sally', 'sally@gmail.com', 'USA'),
(2, 'Salvador Dali', 'wooden', 'Spain'),
(3, 'Joe', 'joe.eh@hotmail.com', 'Canada'),
(4, 'Joel', 'weepingwillowe1985@gmail.com', 'USA');
