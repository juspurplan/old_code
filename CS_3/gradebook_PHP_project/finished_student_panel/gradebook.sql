-- phpMyAdmin SQL Dump
-- version 3.4.5
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Oct 14, 2011 at 05:13 AM
-- Server version: 5.5.16
-- PHP Version: 5.3.8

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `gradebook`
--

-- --------------------------------------------------------

--
-- Table structure for table `assignments`
--

CREATE TABLE IF NOT EXISTS `assignments` (
  `assignment_name` tinytext NOT NULL,
  `assignment_desc` longtext NOT NULL,
  `grade` double NOT NULL,
  `student_id` int(11) NOT NULL,
  `class_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `assignments`
--

INSERT INTO `assignments` (`assignment_name`, `assignment_desc`, `grade`, `student_id`, `class_id`) VALUES
('PHP project', 'Make a website using php and MySQL', 100.01, 123, 1),
('Curve Sketching WS', 'Graph Curves using learned knowledge', 50, 123, 2),
('Ch 3.8 Test', 'Test over Ch 3.8', 200, 123, 2);

-- --------------------------------------------------------

--
-- Table structure for table `classes`
--

CREATE TABLE IF NOT EXISTS `classes` (
  `class_name` tinytext NOT NULL,
  `class_id` int(11) NOT NULL,
  `teacher_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `classes`
--

INSERT INTO `classes` (`class_name`, `class_id`, `teacher_id`) VALUES
('Computer Science III', 1, 1),
('Calculus BC', 2, 1);

-- --------------------------------------------------------

--
-- Table structure for table `students`
--

CREATE TABLE IF NOT EXISTS `students` (
  `student_id` int(11) NOT NULL,
  `username` tinytext NOT NULL,
  `password` tinytext NOT NULL,
  `classes` longtext NOT NULL,
  `name` tinytext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `students`
--

INSERT INTO `students` (`student_id`, `username`, `password`, `classes`, `name`) VALUES
(123, 'alan', 'password', '', 'Alan Tan');

-- --------------------------------------------------------

--
-- Table structure for table `teachers`
--

CREATE TABLE IF NOT EXISTS `teachers` (
  `username` tinytext NOT NULL,
  `password` tinytext NOT NULL,
  `teacher_id` int(11) NOT NULL,
  `name` tinytext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `teachers`
--

INSERT INTO `teachers` (`username`, `password`, `teacher_id`, `name`) VALUES
('jorian', 'password', 1, 'Jorian Khan');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
