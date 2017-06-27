-- phpMyAdmin SQL Dump
-- version 3.3.9
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Oct 14, 2011 at 06:34 PM
-- Server version: 5.5.8
-- PHP Version: 5.3.5

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


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
  `class_id` int(11) NOT NULL,
  `student_id` int(11) NOT NULL,
  `assignment_name` tinytext NOT NULL,
  `assignment_desc` text NOT NULL,
  `grade` double NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `assignments`
--

INSERT INTO `assignments` (`class_id`, `student_id`, `assignment_name`, `assignment_desc`, `grade`) VALUES
(1, 789, 'PHP Project', 'Make a PHP and MySQL website', 100.001),
(2, 789, 'Curve Sketching WS', 'Sketch curves using learned skills', 50),
(2, 789, 'Calculus BC Test ch 3.8', 'test over ch 3.8', 73),
(1, 456, 'PHP Project 	 	', 'Make a PHP and MySQL website', 99.99),
(2, 456, 'Curve Sketching WS ', 'Sketch curves using learned skills', 0),
(2, 456, 'Calculus BC Test ch 3.8 ', 'test over ch 3.8', 85);

-- --------------------------------------------------------

--
-- Table structure for table `classes`
--

CREATE TABLE IF NOT EXISTS `classes` (
  `class_id` int(11) NOT NULL,
  `class_name` tinytext NOT NULL,
  `teacher_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `classes`
--

INSERT INTO `classes` (`class_id`, `class_name`, `teacher_id`) VALUES
(1, 'Computer Science III', 123),
(2, 'Calculus BC', 123);

-- --------------------------------------------------------

--
-- Table structure for table `students`
--

CREATE TABLE IF NOT EXISTS `students` (
  `username` tinytext NOT NULL,
  `student_id` int(11) NOT NULL,
  `firstname` tinytext NOT NULL,
  `lastname` tinytext NOT NULL,
  `classes` longtext NOT NULL,
  `password` tinytext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `students`
--

INSERT INTO `students` (`username`, `student_id`, `firstname`, `lastname`, `classes`, `password`) VALUES
('jorian', 789, 'jorian', 'khan', '', 'password'),
('alan', 456, 'Alan', 'Tan', '', 'password');

-- --------------------------------------------------------

--
-- Table structure for table `teachers`
--

CREATE TABLE IF NOT EXISTS `teachers` (
  `username` tinytext NOT NULL,
  `teacher_id` int(11) NOT NULL,
  `firstname` tinytext NOT NULL,
  `lastname` tinytext NOT NULL,
  `password` tinytext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `teachers`
--

INSERT INTO `teachers` (`username`, `teacher_id`, `firstname`, `lastname`, `password`) VALUES
('hello', 123, 'Mister', 'C', 'world');
