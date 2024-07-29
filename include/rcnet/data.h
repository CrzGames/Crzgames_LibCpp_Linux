#ifndef RCNET_DATA_H
#define RCNET_DATA_H

#include <stddef.h> // Required for : size_t

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Enumération des types de données pris en charge.
 * @typedef {enum} RCNET_DataType
 * @property {number} RCNET_DATA_TYPE_TEXT - Type de données texte.
 * @property {number} RCNET_DATA_TYPE_RAW_DATA - Type de données brutes / binaires.
 */
typedef enum RCNET_DataType {
    RCNET_DATA_TYPE_TEXT,
    RCNET_DATA_TYPE_RAW_DATA
} RCNET_DataType;

/**
 * Enumération des formats d'encodage pris en charge.
 * @typedef {enum} RCNET_EncodeFormat
 * @property {number} RCNET_ENCODE_FORMAT_BASE64 - Format d'encodage Base64.
 * @property {number} RCNET_ENCODE_FORMAT_HEX - Format d'encodage Hexadécimal.
 */
typedef enum RCNET_EncodeFormat {
    RCNET_ENCODE_FORMAT_BASE64,
    RCNET_ENCODE_FORMAT_HEX
} RCNET_EncodeFormat;

/**
 * Structure pour stocker des données encodées ou compressées.
 * 
 * Cette structure contient un pointeur vers les données encodées, 
 * ainsi que des informations sur la taille des données originales 
 * et la taille des données après encodage.
 *
 * @typedef {struct} RCNET_EncodedData
 * @property {char*} data - Pointeur vers les données encodées ou compressées.
 * @property {size_t} originalSize - Taille des données originales.
 * @property {size_t} encodedSize - Taille des données après encodage.
 * @property {RCNET_EncodeFormat} encodeFormat - Format d'encodage utilisé.
 */
typedef struct RCNET_EncodedData {
    char* data;
    size_t originalSize;
    size_t encodedSize;
    RCNET_EncodeFormat encodeFormat;
    RCNET_DataType dataType;
} RCNET_EncodedData;

/**
 * Enumération des formats de compression pris en charge.
 * @typedef {enum} RCNET_CompressFormat
 * @property {number} RCNET_COMPRESS_FORMAT_LZ4 - Format de compression LZ4.
 */
typedef enum RCNET_CompressFormat {
    RCNET_COMPRESS_FORMAT_LZ4
} RCNET_CompressFormat;

/**
 * Cette structure est utilisée pour stocker les résultats d'une opération de compression,
 * incluant à la fois les données compressées elles-mêmes et les informations de taille nécessaires
 * pour la décompression. Elle facilite le passage de ces données à travers les fonctions de
 * compression et de décompression.
 * 
 * @typedef {struct} RCNET_CompressedData
 * @param data Pointeur vers les données compressées doit être libéré par l'appelant.
 * @param originalSize Taille des données d'entrée avant compression. Ceci est nécessaire pour
 *                     la décompression afin de valider l'intégrité des données décompressées.
 * @param compressedSize Taille des données après compression. Ceci est utilisé lors de la
 *                       décompression pour indiquer la quantité de données à traiter.
 * @param compressFormat Format de compression utilisé pour compresser les données.
 * @param dataType Type de données d'entrée, texte ou données brutes.
 */
typedef struct RCNET_CompressedData {
    unsigned char* data;
    size_t originalSize;
    size_t compressedSize; 
    RCNET_CompressFormat compressFormat;
    RCNET_DataType dataType;
} RCNET_CompressedData;

/**
 * Enumération des formats de chiffrement pris en charge.
 * @typedef {enum} RCNET_CipherFormat
 * @property {number} RCNET_CIPHER_FORMAT_AES - Chiffrement AES.
 * @property {number} RCNET_CIPHER_FORMAT_CHACHA20 - Chiffrement ChaCha20.
 * @property {number} RCNET_CIPHER_FORMAT_CHACHA20_POLY1305 - Chiffrement ChaCha20-Poly1305.
 * @property {number} RCNET_CIPHER_FORMAT_RSA - Chiffrement RSA.
 */
typedef enum RCNET_CipherFormat {
    RCNET_CIPHER_FORMAT_AES,
    RCNET_CIPHER_FORMAT_CHACHA20,
    RCNET_CIPHER_FORMAT_CHACHA20_POLY1305,
    RCNET_CIPHER_FORMAT_RSA // TODO: Implement RSA encryption/decryption
} RCNET_CipherFormat;

/**
 * Structure pour stocker des données cryptées.
 *
 * Cette structure contient les informations nécessaires pour stocker des données après qu'elles aient été cryptées.
 * Elle inclut un pointeur vers les données cryptées elles-mêmes, la passphrase utilisée pour le cryptage,
 * ainsi que diverses métadonnées telles que la taille des données originales et cryptées, le format de cryptage utilisé,
 * et le type de données (texte ou données brutes/binaires).
 *
 * @typedef {struct} RCNET_EncryptedData
 * @property {unsigned char*} data - Pointeur vers les données cryptées.
 * @property {char*} passphrase - La passphrase utilisée pour crypter les données et c'est a l'appelant de libérer la mémoire pour des raisons de sécurité.
 * @property {unsigned char*} hmac - Le code d'authentification de message (HMAC) utilisé pour valider l'intégrité des données cryptées.
 * @property {size_t} originalSize - La taille des données originales avant le cryptage.
 * @property {size_t} encryptedSize - La taille des données après le cryptage.
 * @property {size_t} hmacSize - La taille du code d'authentification de message (HMAC).
 * @property {RCNET_CipherFormat} cipherFormat - Le format de chiffrement utilisé pour crypter les données.
 * @property {RCNET_DataType} dataType - Le type de données cryptées, indiquant s'il s'agit de texte ou de données binaires.
 */
typedef struct RCNET_EncryptedData {
    unsigned char* data;
    char* passphrase;
    unsigned char* hmac;
    size_t originalSize;
    size_t encryptedSize;
    size_t hmacSize;
    RCNET_CipherFormat cipherFormat;
    RCNET_DataType dataType;
} RCNET_EncryptedData;

/**
 * Enumération des formats de hachage pris en charge.
 * Cette énumération est utilisée pour spécifier l'algorithme de hachage à utiliser
 * lors du calcul du hachage d'une chaîne de caractères. Chaque valeur représente
 * un algorithme de hachage cryptographique différent, offrant un éventail de choix
 * en fonction des exigences de sécurité et de performance.
 * 
 * @typedef {enum} RCNET_HashFormat
 * @property {number} RCNET_HASHING_FORMAT_MD5 - Algorithme de hachage MD5, produit un hachage de 128 bits. Non recommandé pour une utilisation sécurisée en raison de vulnérabilités connues.
 * @property {number} RCNET_HASHING_FORMAT_SHA1 - Algorithme de hachage SHA-1, produit un hachage de 160 bits. Déconseillé pour une utilisation sécurisée en raison de faiblesses connues.
 * @property {number} RCNET_HASHING_FORMAT_SHA224 - Algorithme de hachage SHA-224, une variante de SHA-2, produit un hachage de 224 bits.
 * @property {number} RCNET_HASHING_FORMAT_SHA256 - Algorithme de hachage SHA-256, une variante de SHA-2, produit un hachage de 256 bits, recommandé pour une utilisation sécurisée.
 * @property {number} RCNET_HASHING_FORMAT_SHA384 - Algorithme de hachage SHA-384, une variante de SHA-2, produit un hachage de 384 bits.
 * @property {number} RCNET_HASHING_FORMAT_SHA512 - Algorithme de hachage SHA-512, une variante de SHA-2, produit un hachage de 512 bits, offrant une sécurité renforcée.
 * @property {number} RCNET_HASHING_FORMAT_SHA3_224 - Algorithme de hachage SHA3-224, produit un hachage de 224 bits, basé sur l'algorithme de hachage Keccak.
 * @property {number} RCNET_HASHING_FORMAT_SHA3_256 - Algorithme de hachage SHA3-256, produit un hachage de 256 bits, basé sur l'algorithme de hachage Keccak.
 * @property {number} RCNET_HASHING_FORMAT_SHA3_384 - Algorithme de hachage SHA3-384, produit un hachage de 384 bits, basé sur l'algorithme de hachage Keccak.
 * @property {number} RCNET_HASHING_FORMAT_SHA3_512 - Algorithme de hachage SHA3-512, produit un hachage de 512 bits, basé sur l'algorithme de hachage Keccak.
 */
typedef enum RCNET_HashFormat {
    RCNET_HASHING_FORMAT_MD5,
    RCNET_HASHING_FORMAT_SHA1,
    RCNET_HASHING_FORMAT_SHA224,
    RCNET_HASHING_FORMAT_SHA256,
    RCNET_HASHING_FORMAT_SHA384,
    RCNET_HASHING_FORMAT_SHA512,
    RCNET_HASHING_FORMAT_SHA3_224,
    RCNET_HASHING_FORMAT_SHA3_256,
    RCNET_HASHING_FORMAT_SHA3_384,
    RCNET_HASHING_FORMAT_SHA3_512
} RCNET_HashFormat;

RCNET_EncodedData* rcnet_data_encode(const unsigned char* data, const size_t dataSize, const RCNET_DataType dataType, const RCNET_EncodeFormat format);
unsigned char* rcnet_data_decode(const RCNET_EncodedData* encodedData);

RCNET_CompressedData* rcnet_data_compress(const unsigned char* data, const size_t dataSize, const RCNET_DataType dataType, const RCNET_CompressFormat format);
unsigned char* rcnet_data_decompress(const RCNET_CompressedData* compressedData);

char* rcnet_data_hash(const char* data, const RCNET_HashFormat format);

RCNET_EncryptedData* rcnet_data_encrypt(const unsigned char* data, const size_t dataSize, const char* passphrase, const RCNET_DataType dataType, const RCNET_CipherFormat format);
unsigned char* rcnet_data_decrypt(const RCNET_EncryptedData* encryptedData);
void rcnet_data_freeSecurity(RCNET_EncryptedData* encryptedData);

#ifdef __cplusplus
}
#endif  

#endif // RCNET_DATA_H