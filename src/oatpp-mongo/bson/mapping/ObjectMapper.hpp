/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *                         Benedikt-Alexander Mokroß <bam@icognize.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#ifndef oatpp_mongo_bson_mapping_ObjectMapper_hpp
#define oatpp_mongo_bson_mapping_ObjectMapper_hpp

#include "./Serializer.hpp"
#include "./Deserializer.hpp"

#include "oatpp/data/mapping/ObjectMapper.hpp"

namespace oatpp { namespace mongo { namespace bson { namespace mapping {

/**
 * BSON ObjectMapper. Serialized/Deserializes oatpp DTO objects to/from BSON.
 * See [Data Transfer Object(DTO) component](https://oatpp.io/docs/components/dto/). <br>
 * Extends &id:oatpp::base::Countable;, &id:oatpp::data::mapping::ObjectMapper;.
 */
class ObjectMapper : public oatpp::base::Countable, public oatpp::data::mapping::ObjectMapper {
private:
  static Info& getMapperInfo() {
    static Info info("application", "bson");
    return info;
  }
private:
  std::shared_ptr<Serializer> m_serializer;
  std::shared_ptr<Deserializer> m_deserializer;
public:
  /**
   * Constructor.
   * @param serializerConfig - &id:oatpp::parser::bson::mapping::Serializer::Config;.
   * @param deserializerConfig - &id:oatpp::parser::bson::mapping::Deserializer::Config;.
   */
  ObjectMapper(const std::shared_ptr<Serializer::Config>& serializerConfig,
               const std::shared_ptr<Deserializer::Config>& deserializerConfig);

  /**
   * Constructor.
   * @param serializer
   * @param deserializer
   */
  ObjectMapper(const std::shared_ptr<Serializer>& serializer = std::make_shared<Serializer>(),
               const std::shared_ptr<Deserializer>& deserializer = std::make_shared<Deserializer>());
public:

  /**
   * Create shared ObjectMapper.
   * @param serializerConfig - &id:oatpp::parser::bson::mapping::Serializer::Config;.
   * @param deserializerConfig - &id:oatpp::parser::bson::mapping::Deserializer::Config;.
   * @return - `std::shared_ptr` to ObjectMapper.
   */
  static std::shared_ptr<ObjectMapper>
  createShared(const std::shared_ptr<Serializer::Config>& serializerConfig,
               const std::shared_ptr<Deserializer::Config>& deserializerConfig);

  /**
   * Create shared ObjectMapper.
   * @param serializer
   * @param deserializer
   * @return
   */
  static std::shared_ptr<ObjectMapper>
  createShared(const std::shared_ptr<Serializer>& serializer = std::make_shared<Serializer>(),
               const std::shared_ptr<Deserializer>& deserializer = std::make_shared<Deserializer>());

  /**
   * Implementation of &id:oatpp::data::mapping::ObjectMapper::write;.
   * @param stream - stream to write serializerd data to &id:oatpp::data::stream::ConsistentOutputStream;.
   * @param variant - object to serialize &id:oatpp::Void;.
   * @param errorStack - See &id:oatpp::data::mapping::ErrorStack;.
   */
  void write(data::stream::ConsistentOutputStream* stream, const oatpp::Void& variant, oatpp::data::mapping::ErrorStack& errorStack) const override;

  /**
   * Implementation of &id:oatpp::data::mapping::ObjectMapper::read;.
   * @param caret - &id:oatpp::utils::parser::Caret;.
   * @param type - type of resultant object &id:oatpp::data::type::Type;.
   * @param errorStack - See &id:oatpp::data::mapping::ErrorStack;.
   * @return - &id:oatpp::Void; holding resultant object.
   */
  oatpp::Void read(oatpp::utils::parser::Caret& caret, const oatpp::data::type::Type* const type, oatpp::data::mapping::ErrorStack& errorStack) const override;


  /**
   * Get serializer.
   * @return
   */
  std::shared_ptr<Serializer> getSerializer();

  /**
   * Get deserializer.
   * @return
   */
  std::shared_ptr<Deserializer> getDeserializer();
  
};
  
}}}}

#endif /* oatpp_mongo_bson_mapping_ObjectMapper_hpp */
