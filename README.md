# Baby Record Store Management System
## Overview
This project is a console-based management system for a continuously operating music store that sells compact discs with recordings of specific performers from various production companies. The system allows for tracking disc inventory, musical compositions, and transaction history, as well as executing analytical queries and enforcing business constraints.
## Project Structure

- `bin/`: Executable files.
- `build/`: Temporary files generated during the build process.
- `includes/`: Header files.
- `src/`: Source files.

## Features
- User authentication and authorization.
- CRUD operations for songs, disks, and transactions.
- Querying sales analysis.

## Setup

1. Clone the repository.
2. Use `make`

## Usage

1. Register a new user or log in as an existing user.
2. Perform operations based on your access level (admin or user).

## Database Schema

- `CD`: Stores information about CD-disks.
- `Songs`: Stores information about songs.
- `Transactions`: Stores information about transactions within the store.
- `Users`: Stores information about users and their access levels.

## Contributing

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Commit your changes and push to your fork.
4. Create a pull request.
