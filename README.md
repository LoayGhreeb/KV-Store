# Key-Value Store

## Overview

The KV-Store project is a simple persistent key-value store written in C. This project serves as a warm-up for the operating systems class (CS-537) and aims to familiarize you with C programming and basic systems programming concepts.

## Project Details

Check out the project [description](https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/initial-kv) for requirements and testing details.

## Usage

The `kv` program provides a set of commands to interact with the key-value store:

- **put**: Insert key-value pairs into the database.
  ```sh
  ./kv p,10,remzi
  ./kv p,20,andrea p,40,someotherperson
  ```

- **get**: Retrieve the value associated with a specific key.
  ```sh
  ./kv g,10
  ```

- **delete**: Delete a key-value pair from the database.
  ```sh
  ./kv d,20
  ```

- **clear**: Remove all key-value pairs from the database.
  ```sh
  ./kv c
  ```

- **all**: Print all key-value pairs in the database.
  ```sh
  ./kv a
  ```
