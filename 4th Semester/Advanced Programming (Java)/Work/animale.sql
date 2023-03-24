-- phpMyAdmin SQL Dump
-- version 5.1.3
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 28, 2022 at 09:27 AM
-- Server version: 10.4.24-MariaDB
-- PHP Version: 8.1.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";

--
-- Database: `tw`
--

-- --------------------------------------------------------

--
-- Table structure for table `animals`
--

CREATE TABLE `animals` (
  `id` int(11) NOT NULL,
  `name` text NOT NULL,
  `region` text NOT NULL,
  `habitat` text NOT NULL,
  `tip` text NOT NULL,
  `conservation` text NOT NULL,
  `image` text NOT NULL,
  `description` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `animals`
--

INSERT INTO `animals` (`id`, `name`, `region`, `habitat`, `tip`, `conservation`, `image`, `description`) VALUES
(1, 'Acvila Codalb', 'Asia', 'Forest', 'Birds', 'Extinction', 'https://i.imgur.com/BLlyQDP.jpg', 'Codalbul, cunoscut și sub denumirea de Vultur cu coada albă, este o pasăre de pradă diurnă, monogamă ce tinde să își păstreze perechea toată viața. Vânează printr-un zbor jos deasupra apei de unde își prinde prada sau poate realiza cercuri largi la 200 – 300 m înălțime, de unde se uită după pradă. La sfârșitul lunii aprilie și începutul lunii mai, când peștii depun icrele, stă nemișcat în ape mici și prinde cu sărituri rapide, peștii care trec prin apropiere. Se poate scufunda, dar o face rar.'),
(2, 'Agama cu barba', 'Australia', 'Forest', 'Reptiles', 'Stable', 'https://i.imgur.com/EpSIHWy.jpg', 'Ambele sexe au o barbă, dar masculii o afișează mai frecvent, mai ales pentru ritualuri de reproducere. Femelele își vor arăta barba ca pe un semn de agresiune. Barba devine întunecată în negru și se umflă în timpul afișării. Masculul de agamă cu barbă poate să-și deschidă, de asemenea, gura, pentru a părea mai intimidant. Dragonul bărbos stă pe 3 picioare și se rotește într-un model circular lent. Se pare că dragonul bărbos se mișcă bine sau înotând cu un singur braț.'),
(3, 'Alpaca', 'America', 'Forest', 'Mammals', 'Stable', 'https://i.imgur.com/XWKA4rQ.jpg', 'Alpaca, animal erbivor originar din Anzii Cordilieri, face parte din familia cămilei, fiind înrudită cu lama, guanaco-ul și vicunia din America de Sud, precum și cu cămilele bactriane și dromadere din Asia și Africa.'),
(4, 'Anaconda Verde', 'America', 'Forest', 'Reptiles', 'Stable', 'https://i.imgur.com/wcHeUJD.jpg', 'Anaconda verde (Eunectes murinus), cunoscută și ca anaconda obișnuită sau boa de apă, este o specie de șarpe din America de Sud, fiind cel mai mare șarpe din lume. În sălbăticie au fost descoperite  anaconde de 10 până la 12 metri care cântăresc și peste 250 kg, deși dimensiunea maximă reală a unei anaconda este subiectul multor cotroverse. Femelele au în mod obișnuit o greutate și o lungime mult mai mari decât masculii, aceștia atingând o lungime medie de 3 metri și femelele de 6 metri. Sexul unei anaconda este reflectat de mărimea pintenilor situați în regiunea cloacală. Masculii au crestături mai mari (7,5 milimetri) decât femelele.');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `animals`
--
ALTER TABLE `animals`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `animals`
--
ALTER TABLE `animals`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
COMMIT;