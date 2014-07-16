--
-- PostgreSQL database dump
--

SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

--
-- Name: SCHEMA public; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON SCHEMA public IS 'Standard public schema';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: books; Type: TABLE; Schema: public; Owner: openlib; Tablespace: 
--

CREATE TABLE books (
    id integer NOT NULL,
    book_id integer DEFAULT 0 NOT NULL,
    name character varying(255) DEFAULT ''::character varying NOT NULL,
    orig character varying(255),
    author text NOT NULL,
    pages integer DEFAULT 0 NOT NULL,
    publisher character varying(255) NOT NULL,
    isbn text NOT NULL,
    lang character varying(2) DEFAULT 'ru'::character varying NOT NULL,
    mime character varying(4) DEFAULT 'pdf'::character varying NOT NULL,
    size numeric(5,2) DEFAULT 0.00 NOT NULL,
    size_char character varying(2) DEFAULT 'mb'::character varying NOT NULL,
    category character varying(4) DEFAULT '10'::character varying NOT NULL,
    "show" character varying(1) DEFAULT '1'::character varying NOT NULL,
    short_descr text NOT NULL,
    full_descr text NOT NULL,
    who_add integer DEFAULT 0 NOT NULL,
    date date NOT NULL,
    watch integer DEFAULT 0 NOT NULL,
    rate integer DEFAULT 0 NOT NULL,
    download_rate integer DEFAULT 0 NOT NULL,
    url text NOT NULL,
    img character varying(1) DEFAULT '1'::character varying NOT NULL,
    CONSTRAINT books_category_check CHECK (((category)::text = ANY ((ARRAY['10'::character varying, '20'::character varying, '30'::character varying, '40'::character varying, '50'::character varying, '60'::character varying, '70'::character varying, '80'::character varying, '90'::character varying, '100'::character varying, '110'::character varying, '120'::character varying, '130'::character varying, '140'::character varying, '150'::character varying, '160'::character varying, '170'::character varying, '180'::character varying, '190'::character varying, '200'::character varying, '210'::character varying, '220'::character varying, '230'::character varying, '240'::character varying, '250'::character varying, '260'::character varying, '270'::character varying, '280'::character varying, '290'::character varying, '300'::character varying, '310'::character varying, '320'::character varying, '330'::character varying, '340'::character varying, '350'::character varying, '360'::character varying, '370'::character varying, '380'::character varying, '390'::character varying, '400'::character varying, '410'::character varying, '420'::character varying, '430'::character varying, '440'::character varying, '450'::character varying, '460'::character varying, '470'::character varying, '480'::character varying, '490'::character varying, '500'::character varying, '510'::character varying, '520'::character varying, '530'::character varying, '540'::character varying, '550'::character varying, '560'::character varying, '570'::character varying, '580'::character varying, '590'::character varying, '600'::character varying, '610'::character varying, '620'::character varying, '630'::character varying, '640'::character varying, '650'::character varying, '660'::character varying, '670'::character varying, '680'::character varying, '690'::character varying, '700'::character varying, '710'::character varying, '720'::character varying, '730'::character varying, '740'::character varying, '750'::character varying, '760'::character varying, '770'::character varying, '780'::character varying, '790'::character varying, '800'::character varying, '810'::character varying, '820'::character varying, '830'::character varying, '840'::character varying, '850'::character varying, '860'::character varying, '870'::character varying, '880'::character varying, '890'::character varying, '900'::character varying, '910'::character varying, '920'::character varying, '930'::character varying, '940'::character varying, '950'::character varying, '960'::character varying, '970'::character varying, '980'::character varying, '990'::character varying, '1000'::character varying, '1010'::character varying, '1020'::character varying, '1030'::character varying, '1040'::character varying, '1050'::character varying, '1060'::character varying, '1070'::character varying, '1080'::character varying, '1090'::character varying, '1100'::character varying, '1110'::character varying, '1120'::character varying, '1130'::character varying, '1140'::character varying])::text[]))),
    CONSTRAINT books_img_check CHECK (((img)::text = ANY ((ARRAY['0'::character varying, '1'::character varying])::text[]))),
    CONSTRAINT books_lang_check CHECK (((lang)::text = ANY ((ARRAY['ru'::character varying, 'en'::character varying, 'ua'::character varying])::text[]))),
    CONSTRAINT books_mime_check CHECK (((mime)::text = ANY ((ARRAY['pdf'::character varying, 'djvu'::character varying, 'html'::character varying, 'chm'::character varying, 'doc'::character varying, 'txt'::character varying, 'ps'::character varying, 'odt'::character varying])::text[]))),
    CONSTRAINT books_show_check CHECK ((("show")::text = ANY ((ARRAY['1'::character varying, '0'::character varying])::text[]))),
    CONSTRAINT books_size_char_check CHECK (((size_char)::text = ANY ((ARRAY['kb'::character varying, 'mb'::character varying])::text[])))
);


ALTER TABLE public.books OWNER TO openlib;

--
-- Name: books_category; Type: TABLE; Schema: public; Owner: root; Tablespace: 
--

CREATE TABLE books_category (
    id integer NOT NULL,
    step integer,
    id_category integer,
    id_menu character varying(2),
    category_name character varying(255),
    category integer,
    CONSTRAINT books_category_id_category_check CHECK ((id_category = ANY (ARRAY[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000, 1010, 1020, 1030, 1040, 1050, 1060, 1070, 1080, 1090, 1100, 1110, 1120, 1130, 1140, 1150, 1160, 1170, 1180, 1190, 1200, 1210, 1220, 1230, 1240, 1250, 1260, 1270, 1280, 1290, 1300, 1310, 1320, 1330, 1340, 1350, 1360, 1370, 1380, 1390, 1400, 1410, 1420, 1430, 1440, 1450, 1460, 1470, 1480, 1490, 1500, 1510, 1520, 1530, 1540, 1550, 1560, 1570, 1580, 1590, 1600, 1610, 1620, 1630, 1640, 1650, 1660, 1670, 1680, 1690, 1700, 1710, 1720, 1730, 1740, 1750, 1760, 1770, 1780, 1790, 1800, 1810, 1820, 1830, 1840, 1850, 1860, 1870, 1880, 1890, 1900, 1910, 1920, 1930, 1940, 1950, 1960, 1970, 1980, 1990]))),
    CONSTRAINT books_category_id_menu_check CHECK (((id_menu)::text = ANY ((ARRAY['s'::character varying, 'm'::character varying])::text[])))
);


ALTER TABLE public.books_category OWNER TO root;

--
-- Name: books_pkey; Type: CONSTRAINT; Schema: public; Owner: openlib; Tablespace: 
--

ALTER TABLE ONLY books
    ADD CONSTRAINT books_pkey PRIMARY KEY (id);


--
-- Name: id_primery; Type: CONSTRAINT; Schema: public; Owner: root; Tablespace: 
--

ALTER TABLE ONLY books_category
    ADD CONSTRAINT id_primery PRIMARY KEY (id);


--
-- Name: id; Type: INDEX; Schema: public; Owner: root; Tablespace: 
--

CREATE UNIQUE INDEX id ON books_category USING btree (id);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

