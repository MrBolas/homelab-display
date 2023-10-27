import GardenClient from "../../client/garden";
import React, { useEffect, useState } from "react";
import emptyImage from "../../assets/waterlevel/empty.png"
import fullImage from "../../assets/waterlevel/full.png"

function WaterLevel() {
  const [waterStatus, setWaterStatus] = useState("");
  const fetchWaterLevel = async () => {
    const client = new GardenClient("http://localhost:8080");
    return client.hasWater()
      .then(waterlevel => {
        if (waterlevel.HasWater) {
          setWaterStatus("Has Water");
        } else {
          setWaterStatus("Is Empty");
        }
      }).catch(error => {
        setWaterStatus("Error");
      });
  };

  useEffect(() => {
    fetchWaterLevel();
    const interval = setInterval(() => {
      fetchWaterLevel();
    }, 15000);
    return () => {
      clearInterval(interval);
    };
  }, []);

  return (
    <div >
      <h1>Water Level</h1>
      <div class="position-absolute top-50 start-50 translate-middle">
        {console.log(waterStatus)}
        {waterStatus === "Has Water" ? (
          <img src={fullImage} alt="Has Water" width="500" height="500"/>
        ) : (
          <img src={emptyImage} alt="No Water" width="500" height="500" />
        )}
      </div>
      <button onClick={fetchWaterLevel}>Check Water Level</button>
    </div>
  );
}

export default WaterLevel;
